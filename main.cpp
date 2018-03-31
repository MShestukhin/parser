#include <iostream>
#include <postgresql/libpq-fe.h>
#include <string.h>
#include <vector>
#include <dirent.h>]
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <vector>
#include <algorithm>
using namespace std;
PGconn* conn;
PGresult* res;
struct line
{
    char* date;
    char* number;
    char* number_2;
    char* number_3;
    char* call_duration;
    char* res;
    line() {
        date;
        number="";
        number_2="";
        number_3="";
        call_duration="";
        res="";
    }
};

void send_to_db(std::vector<line> massln){

    for(int i=0; i<massln.size();i++){
    const char* paramValues[6]={ (char*)massln.at(i).date,(char*)massln.at(i).number,(char*)massln.at(i).number_2,(char*)massln.at(i).number_3,(char*)massln.at(i).call_duration,(char*)massln.at(i).res};
    res=PQexecParams(conn,
                     "INSERT INTO steer_web.eir_test (date, number_1, number_2, number_3, duration, result) VALUES($1, $2, $3, $4, $5, $6)",
                     6,
                     NULL,
                     paramValues,
                     NULL,
                     NULL,
                     1);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "INSERT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
    }
    PQclear(res);
    delete massln.at(i).date;
    delete massln.at(i).number;
    delete massln.at(i).number_2;
    delete massln.at(i).number_3;
    delete massln.at(i).call_duration;
    delete massln.at(i).res;
    }
}

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
    char* str;
    str=(char*)malloc(100);
    char* pointer=(char*)&buf;
    line ln;
        while(*pointer!='\0'){
            if(*pointer!=','){
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
                    ln.number=new char(strlen(str));
                    strcpy(ln.number,str);
                    break;
                case 2:
                    ln.number_2=new char(strlen(str));
                    strcpy(ln.number_2,str);
                    break;
                case 3:
                    ln.number_3=new char[strlen(str)];
                    strcpy(ln.number_3,str);
                    break;
                case 4:
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
}

struct file_data
{
    int file_mtime;
    std::string name;
    file_data() {
        file_mtime=0;
        name="";
    }
};

bool myfunction (file_data i,file_data j) {
    return (i.file_mtime>j.file_mtime); }

int main()
{
    conn = PQconnectdb("dbname=steer_main host=172.18.1.82 user=postgres password=terrm1nator");
    if (PQstatus(conn) == CONNECTION_BAD) {
        puts("We were unable to connect to the database");
    }
    DIR* dir;
    struct dirent* entry;
    struct stat sb;
    std::string strDir="./fileFolder";
    while (1) {
    vector<file_data> vdata_file;
    dir=opendir(strDir.c_str());
    if(dir==NULL){
        perror("Can not open dir");
    }
    while ((entry=readdir(dir))!=NULL) {
        std::string str_file=entry->d_name;
        std::string str_dir_file=strDir+"/"+str_file;
        if(str_file!="."&&str_file!=".."){
            file_data time_name_file;
            stat((char*)str_dir_file.c_str(),&sb);
            time_name_file.file_mtime=sb.st_mtim.tv_sec;
            time_name_file.name=str_dir_file;
            vdata_file.push_back(time_name_file);
        }
    }
    std::sort (vdata_file.begin(), vdata_file.end(), myfunction);
    for(int i=0;i<vdata_file.size();i++){
        cout<<i<<"-"<<vdata_file.at(i).name;
        pars_file(vdata_file.at(i).name);
        std::string str="mv "+vdata_file.at(i).name+" ./New_Test_folder";
        system(str.c_str());
        cout<<"\n";
    }
    closedir(dir);
    }
    PQfinish(conn);
    PQisBusy(conn);
    return 0;
}
