#include <iostream>
#include <fstream>
#include <string.h>
#include <postgresql/libpq-fe.h>
using namespace std;
struct line
{
    std::string date;
    std::string number;
    std::string number_2;
    std::string number_3;
    std::string call_duration;
    std::string res;
    line() {
        date="";
        number="";
        number_2="";
        number_3="";
        call_duration="";
        res="";
    }
};
int main()
{
    PGconn* conn;
    conn=PQconnectdb("dbname=mudb");
    FILE* file;
    char* nameFile="file_numbers.csv";
    file=fopen(nameFile,"r");
    if(file == NULL)
    {
        printf("не могу открыть файл");
        return 0;
    }
    line massln[10];
    int iter=0;
    while(!feof(file)){
    int i=0;
    int j=0;
    line ln;
    char buf[100];
    fgets(buf,100,file);
    char* str;
    str=(char*)malloc(10);
    char* pointer=(char*)&buf;
    while(*pointer!='\0'){
        if(*pointer!=';'){
            str[j++]=*pointer;
            pointer++;
        }
        else{
            str[j]='\0';
            j=0;
            pointer++;
            switch (i) {
            case 0:
                ln.date=std::string(str);
                break;
            case 1:
                ln.number=std::string(str);
                break;
            case 2:
                ln.number_2=std::string(str);
                break;
            case 3:
                ln.number_3=std::string(str);
                break;
            case 4:
                ln.call_duration=std::string(str);
                str[j++]=*pointer;
                str[j]='\0';
                ln.res=std::string(str);
                break;
            default:
                break;
            }
            i++;
        }
    }
    massln[iter]=ln;
    cout<<massln[iter].date<<'\n';
    cout<<massln[iter].number<<'\n';
    cout<<massln[iter].number_2<<'\n';
    cout<<massln[iter].number_3<<'\n';
    cout<<massln[iter].call_duration<<'\n';
    cout<<massln[iter].res<<'\n';
    memset(buf,' ',100);
    iter++;
    if(iter==9){ iter=0;}
    }
    fclose(file);
    return 0;
}
