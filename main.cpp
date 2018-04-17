#include <iostream>
#include "main.h"
src::severity_logger< severity_level > lg;
PGconn* conn;
Data_from_conf_file* conf_data;
vector<std::string>* table_name;
vector<std::string>* table_file_name;
    //функция отправки данных в базу
void INSERT(std::string insert_cmd_str,  char* paramValues[],int num_param){
    PGresult* res;
    int length[sizeof(paramValues)];
    for(int i=0; i<sizeof(paramValues);i++){
        length[i]=strlen(paramValues[i]);
        /*std::cout<<i<<"\n";
        std::cout<<paramValues[i]<<"\n";*/
    }
    res=PQexecParams(conn,
                     insert_cmd_str.c_str(),
                     num_param,
                     NULL,
                     paramValues,
                     NULL,
                     NULL,
                     1);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("INSERT failed: %s", PQerrorMessage(conn));
        BOOST_LOG_SEV(lg, error) <<"INSERT failed: "<<PQerrorMessage(conn);
        raise(SIGABRT);
    }
    PQclear(res);
}

void prepare_query_and_insert(vector<vector<std::string> > massln, std::string table_name, vector<std::string>* table_field){
    char* paramValues[massln.at(0).size()];
    for(int j=0;j<massln.size();j++){
        for(int i=0;i<massln.at(j).size();i++){
            paramValues[i]=(char*)massln.at(j).at(i).c_str();
            //std::cout<<paramValues[i]<<"\n";
        }
    }
    std::string insert_begin="INSERT INTO "+conf_data->str_dbschema+"."+table_name+" (";
    std::string insert_end=") VALUES(";
    for(int i=0;i<table_field->size();i++){
        insert_begin=insert_begin+table_field->at(i);
        char n[10];
        sprintf(n,"%d",i+1);
        insert_end=insert_end+"$"+n;
        if((i+1)!=table_field->size()){
            insert_end+=",";
            insert_begin+=",";
        }
    }
    std::string insert_cmd_str=insert_begin+insert_end+")";
    std::cout<<insert_cmd_str<<"\n";
    INSERT(insert_cmd_str,paramValues,massln.at(0).size());
}

    //вспомогательная функция для упорядочения массива с именами файлов в порядке времени их изменения
bool myfunction (file_data i,file_data j) {
    return (i.file_mtime>j.file_mtime);
}

    //хендлер корректного завершения програмы
void finish_prog_func(int sig){
    PQfinish(conn);
    printf("program finish");
    BOOST_LOG_SEV(lg, info)<<"Program finish";
    exit(0);
}

    //хендлер аварийного завершения программы
void sig_abort_func(int sig){
    PQfinish(conn);
    std::string str="netstat -anp | grep ':5432' | awk '{print $7}' | grep -oE [[:digit:]]{1,} | xargs kill";
    //system(str.c_str());
    BOOST_LOG_SEV(lg, fatal)<<"Program abort";
    exit(0);
}

    //инициализация файла конфигураций и логирования
void init()
{
    libconfig::Config conf;
    try{
            conf.readFile("/opt/svyazcom/etc/cdr_sca.conf");
        }
    catch(libconfig::ParseException e){
             BOOST_LOG_SEV(lg, fatal) << e.getError() << " line:" << e.getLine() << std::endl;
        }
    conf_data=new Data_from_conf_file(
              conf.lookup("application.paths.sourceDir"),
              conf.lookup("application.paths.trashDir"),
              conf.lookup("application.paths.workOutDir"),
              conf.lookup("application.dataBase.dbname"),
              conf.lookup("application.dataBase.host"),
              conf.lookup("application.dataBase.user"),
              conf.lookup("application.dataBase.password"),
              conf.lookup("application.dataBase.table"),
              conf.lookup("application.dataBase.schema"),
              conf.lookup("application.dataBase.for_done_file_table"));

    table_name=new vector<std::string>;
    int number_of_table=conf.lookup("application.tableData").getLength();
    for(int i=0;i<number_of_table;i++){
        table_name->push_back(conf.lookup("application.tableData")[i]);
    }

    table_file_name=new vector<std::string>;
    number_of_table=conf.lookup("application.tableFileData").getLength();
    for(int i=0;i<number_of_table;i++){
        table_file_name->push_back(conf.lookup("application.tableFileData")[i]);
    }


    std::string log_path_str= conf.lookup("application.paths.logDir");

    logging::add_file_log
    (
        keywords::file_name =log_path_str+ "/%Y-%m-%d.log",
                keywords::auto_flush = true ,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format =
        (
            expr::stream
            << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
            << "\t: <" << logging::trivial::severity
            << "> \t" << expr::smessage
        )
    );

}

void CONNECT(){
    std::string str_connect_to_db="dbname="+conf_data->str_dbname+" host="+conf_data->str_dbhost+" user="+conf_data->str_dbuser+" password="+conf_data->str_dbpassword;
    conn=PQconnectdb(str_connect_to_db.c_str());
    if (PQstatus(conn) == CONNECTION_BAD) {
        puts("We were unable to connect to the database");
        BOOST_LOG_SEV(lg, fatal)<<"Failed connection to the database";
    }
}

int main()
{
    signal(SIGINT, finish_prog_func);
    signal(SIGABRT,sig_abort_func);
    init();
    logging::add_common_attributes();
    BOOST_LOG_SEV(lg, info) << "Begin program";
    //подключение к базе
    boost::thread thread(&CONNECT);
    thread.join();
    //начало работы с диррикториями
    DIR* dir;
    struct dirent* entry;
    struct stat sb;
    //начало цикла проверки наличия файлов в папке
    while (1) {
    sleep(5);
    vector<file_data> vdata_file;
    dir=opendir(conf_data->str_dir.c_str());
        if(dir==NULL){
            cout<<"Can not open folder ";
            BOOST_LOG_SEV(lg, fatal) <<"Can not open dir "<<stderr;
            return 1;
        }

        while ((entry=readdir(dir))!=NULL) {
            std::string str_file=entry->d_name;
            std::string str_dir_file=conf_data->str_dir+"/"+str_file;
            //если в папке есть файлы cмотрим какие
            if(str_file!="."&&str_file!=".."){
                file_data time_name_file;
                stat((char*)str_dir_file.c_str(),&sb);
                //если в папке есть файлы расширения .cdr заносим в буфер
                if(S_ISREG(sb.st_mode)){
                    size_t pos=str_file.rfind(".");
                    std::string ext=str_file.substr(pos, string::npos);
                    if(ext==".cdr"){
                    time_name_file.file_mtime=sb.st_mtim.tv_sec;
                    time_name_file.name=str_dir_file;
                    vdata_file.push_back(time_name_file);
                    }
                }
            }
        }
    //сортируем в порядке времени изменения файла
    std::sort (vdata_file.begin(), vdata_file.end(), myfunction);
    //отправляем парсеру найденые файлы с расширением .cdr
    for(int i=0;i<vdata_file.size();i++){
        std::string file_name= vdata_file.at(i).name;
        size_t pos=file_name.rfind("/");
        std::string name_for_db=file_name.substr(pos+1,string::npos);
        PGresult   *res;
        res = PQexec(conn, "SELECT * FROM steer.cdr_sc_done_files");
            if (PQresultStatus(res) != PGRES_TUPLES_OK)         /* did the query fail? */
               {
               fprintf(stderr, "SELECT query failed.\n");
               PQclear(res);
               PQfinish(conn);
               exit(1);
               }
            bool exist=false;
               for (i = 0; i < PQntuples(res); i++)  {
               std::string strike_string=PQgetvalue(res, i, 0);
               if(name_for_db==strike_string){
                   BOOST_LOG_SEV(lg, info) << "File already exist "<<file_name;
                   std::cout<<"File already exist "<<file_name;
                   std::string str_result_cmd="mv "+file_name+" "+conf_data->str_dir+"-f";
                   system(str_result_cmd.c_str());
                   exist=true;
                   break;
               }
               }
               PQclear(res);
               if(!exist){
                   BOOST_LOG_SEV(lg, info) << "Read file "<<file_name;
                   parser Parser;
                   vector<vector<std::string> > rows=Parser.pars_file(file_name,table_name->size(),2);
                   std::string str_result_cmd;
                   if(rows.size()>0){
                       Parser.transform_to_timestamp_promat(&rows,0);
                       prepare_query_and_insert(rows,conf_data->str_dbtable, table_name);
                       BOOST_LOG_SEV(lg, info)<<file_name<<" successfully write to database";
                       str_result_cmd="mv "+file_name+" "+conf_data->str_workOut_dir;
                       vector<vector<std::string> > file_datas;
                       vector<std::string> file_data;
                       file_data.push_back(name_for_db);
                       char line[10];
                       sprintf(line,"%d",rows.size());
                       file_data.push_back(line);
                       sprintf(line,"%d",Parser.mass_broken_ln.size());
                       file_data.push_back(line);
                       file_datas.push_back(file_data);
                       prepare_query_and_insert(file_datas,conf_data->str_db_for_files_table, table_file_name);
                   }
                   if(Parser.mass_broken_ln.size()>0){
                       //заносим битые строки в файл и отправляем его в корзину, пишем результат в лог
                       BOOST_LOG_SEV(lg, error)<<"Error format file "<<file_name;
                       str_result_cmd="mv "+file_name+" "+conf_data->str_trash_dir+" -f";
                       system(str_result_cmd.c_str());
                       FILE* file;
                       file_name=file_name+".part";
                       char* nameFile=(char*)file_name.c_str();

                       file=fopen(nameFile,"w");
                       if(file == NULL)
                       {
                            //написать в лог что файл на запись открыть не удалось
                            BOOST_LOG_SEV(lg, error)<<"Can not open file for writing "<<file_name;
                            std::cout<<"File for writen not open\n";
                       }
                       else{
                           int i=0;
                           while(i<Parser.mass_broken_ln.size()){
                               fputs(Parser.mass_broken_ln.at(i).c_str(), file);
                               fputs("\n", file);
                               i++;
                           }
                           fclose(file);
                           str_result_cmd="mv "+file_name+" "+conf_data->str_trash_dir+" -f";
                       }
                   }
                   BOOST_LOG_SEV(lg, info)<<str_result_cmd;
                   system(str_result_cmd.c_str());
               }
               }
    closedir(dir);
    }
    PQfinish(conn);
    return 0;
}
