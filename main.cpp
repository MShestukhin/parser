#include <iostream>
#include "main.h"

src::severity_logger< severity_level > lg;
PGconn* conn;
Data_from_conf_file* conf_data;
Table_conf_data* table_conf_data;
//функция отправки данных в базу
void send_to_db(std::vector<line> massln){
    PGresult* res;
    for(int i=0; i<massln.size();i++){
    const char* paramValues[7]={ (char*)massln.at(i).date,(char*)massln.at(i).imsi, (char*)massln.at(i).number,(char*)massln.at(i).number_2,(char*)massln.at(i).number_3,(char*)massln.at(i).call_duration,(char*)massln.at(i).res};
    //std::string insert_cmd_str="INSERT INTO "+conf_data->str_dbschema+"."+conf_data->str_dbtable+" (date, imsi, number_1, number_2, number_3, duration, result) VALUES($1, $2, $3, $4, $5, $6, $7)";
    std::string insert_cmd_str="INSERT INTO "+
            conf_data->str_dbschema+"."+conf_data->str_dbtable+" ("+
            table_conf_data->timestamp+","+
            table_conf_data->imsi+","+
            table_conf_data->number_1+","+
            table_conf_data->number_2+","+
            table_conf_data->number_3+","+
            table_conf_data->duration+","+
            table_conf_data->result+")VALUES($1, $2, $3, $4, $5, $6, $7)";
    res=PQexecParams(conn,
                     insert_cmd_str.c_str(),
                     7,
                     NULL,
                     paramValues,
                     NULL,
                     NULL,
                     1);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "INSERT failed: %s", PQerrorMessage(conn));
        BOOST_LOG_SEV(lg, error) <<"INSERT failed: "<<PQerrorMessage(conn);
        PQclear(res);
        PQfinish(conn);
    }
    PQclear(res);
    delete massln.at(i).date;
    delete massln.at(i).imsi;
    delete massln.at(i).number;
    delete massln.at(i).number_2;
    delete massln.at(i).number_3;
    delete massln.at(i).call_duration;
    delete massln.at(i).res;
    }
}

/*class Parser{
private :
    //вспомогательная функция используется для приведения значения дата к формату таймстамп
    void transform_to_timestamp_promat(char* newNumber,char* str){
        int j=0;
        while (*str!='\0') {
         newNumber[j++]=*str;
         switch (j) {
         case 4:
            newNumber[j++]='-';
             break;
         case 7:
             newNumber[j++]='-';
             break;
         case 10:
             newNumber[j++]=' ';
             break;
         case 13:
             newNumber[j++]=':';
             break;
         case 16:
             newNumber[j++]=':';
             break;
         default:
             break;
         }
         str++;
        }
        newNumber[j++]='\0';
    }

public :
    Parser(){

    }

    int pars_file(std::string file_name){
        FILE* file;
        char* nameFile=(char*)file_name.c_str();
        file=fopen(nameFile,"r");
        if(file == NULL)
        {
            printf("can not open file");
            return 2;
        }
        std::vector<line> massln;
        int iter=0;
        while(!feof(file)){
        int i=0;
        int j=0;
        char buf[100];
        fgets(buf,100,file);
        if(strlen(buf)==0){
            break;
        }
        std::string s1(buf);
        char comma=',';
        char delimiter;
        std::string::size_type n = s1.find(comma);
        if ( n != std::string::npos )
        {
            delimiter=comma;
        }
        else{
            delimiter=';';
        }
        char* str;
        str=(char*)malloc(100);
        char* pointer=(char*)&buf;
        line ln;
        while(*pointer!='\0'){
                if(*pointer!=delimiter){
                    str[j++]=*pointer;
                    pointer++;
                }
                else{
                    str[j]='\0';
                    j=0;
                    pointer++;
                    switch (i) {
                    case 0:
                        char* point;
                        point=(char*)malloc(100);
                        transform_to_timestamp_promat(point,str);
                        ln.date=new char[strlen(point)];
                        strcpy(ln.date,point);
                        break;
                    case 1:
                        ln.imsi=new char(strlen(str));
                        strcpy(ln.imsi,str);
                       break;
                    case 2:
                        ln.number=new char(strlen(str));
                        strcpy(ln.number,str);
                        break;
                    case 3:
                        ln.number_2=new char(strlen(str));
                        strcpy(ln.number_2,str);
                        break;
                    case 4:
                        ln.number_3=new char[strlen(str)];
                        strcpy(ln.number_3,str);
                        break;
                    case 5:
                        ln.call_duration=new char[strlen(str)];
                        strcpy(ln.call_duration,str);
                        str[j++]=*pointer;
                        str[j]='\0';
                        ln.res=new char[strlen(str)];
                        strcpy(ln.res,str);
                        break;
                    default:
                        break;
                    }
                    i++;
                }
            }
        if(i<6){
            std::string trashDir=conf_data->str_trash_dir;
            BOOST_LOG_SEV(lg, error) <<"Error format file \n"<<trashDir;
            std::string str="mv "+file_name+" "+trashDir;
            system(str.c_str());
        }
            massln.push_back(ln);
            memset(buf,0,100);
            if((massln.size()%10)==0){
                iter=0;
                send_to_db(massln);
                massln.clear();
            }
        }
        fclose(file);
        if(massln.size()>0){
            send_to_db(massln);
        }
        BOOST_LOG_SEV(lg, info) << "Succied write to db file "<<file_name;
    }
};*/

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
    BOOST_LOG_SEV(lg, fatal)<<"Program abort";
    exit(0);
}

//инициализация файла конфигураций и логирования
void init()
{
    libconfig::Config conf;
    try{
            conf.readFile("config.conf");
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
              conf.lookup("application.dataBase.schema"));

     table_conf_data=new Table_conf_data(
                 conf.lookup("application.tableData.timestamp"),
                 conf.lookup("application.tableData.imsi"),
                 conf.lookup("application.tableData.number_1"),
                 conf.lookup("application.tableData.number_2"),
                 conf.lookup("application.tableData.number_3"),
                 conf.lookup("application.tableData.duration"),
                 conf.lookup("application.tableData.result"));

    logging::add_file_log
    (
        keywords::file_name = "./log/logFile_%N.log",
        keywords::rotation_size = 10 * 1024,
        keywords::format =
        (
            expr::stream
            << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
            << "\t: <" << logging::trivial::severity
            << "> \t" << expr::smessage
        )
    );
}

int main()
{
    signal(SIGINT, finish_prog_func);
    signal(SIGABRT,sig_abort_func);
    init();
    logging::add_common_attributes();
    BOOST_LOG_SEV(lg, info) << "Begin program";
    //подключение к базе
    std::string str_connect_to_db="dbname="+conf_data->str_dbname+" host="+conf_data->str_dbhost+" user="+conf_data->str_dbuser+" password="+conf_data->str_dbpassword;
    conn = PQconnectdb(str_connect_to_db.c_str());
    if (PQstatus(conn) == CONNECTION_BAD) {
        puts("We were unable to connect to the database");
        BOOST_LOG_SEV(lg, fatal)<<"Failed connection to the database";
        return 1;
    }
    //начало работы с диррикториями
    DIR* dir;
    struct dirent* entry;
    struct stat sb;
    //начало цикла проверки наличия файлов в папке
    while (1) {
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
            //если в папке есть файлы расширения .csv заносим в буфер
            if(S_ISREG(sb.st_mode)&&str_file.find(".csv")!=std::string::npos){
                time_name_file.file_mtime=sb.st_mtim.tv_sec;
                time_name_file.name=str_dir_file;
                vdata_file.push_back(time_name_file);
            }
            //в противном случае переносим в папку для мусора и файлы и папки
            else{
                BOOST_LOG_SEV(lg, warning) << str_dir_file<<" droped because of : not .csv file ";
                std::string str="mv "+str_dir_file+" "+conf_data->str_trash_dir+" -f";
                system(str.c_str());
            }
        }
    }
    //сортируем в порядке времени изминения файла
    std::sort (vdata_file.begin(), vdata_file.end(), myfunction);
    //отправляем парсеру найденые файлы с расширением .csv
    for(int i=0;i<vdata_file.size();i++){
        std::string file_name= vdata_file.at(i).name;
        cout<<file_name;
        BOOST_LOG_SEV(lg, info) << "Read file "<<file_name;
        parser Parser;
        int pars_res=Parser.pars_file(file_name);
        std::string str;
        switch (pars_res){
        case 0:
            BOOST_LOG_SEV(lg, info)<<file_name<<" successfully write to database";
            str="mv "+file_name+" "+conf_data->str_workOut_dir;
            break;
        case 1:
            BOOST_LOG_SEV(lg, error)<<"Can not open file "<<file_name;
            str="mv "+file_name+" "+conf_data->str_trash_dir+" -f";
            break;
        case 2:
            BOOST_LOG_SEV(lg, error)<<"Error format file "<<file_name;
            str="mv "+file_name+" "+conf_data->str_trash_dir+" -f";
            break;
        default:
            break;
        }
       system(str.c_str());
    }
    closedir(dir);
    }
    PQfinish(conn);
    return 0;
}
