#include <iostream>
#include <postgresql/libpq-fe.h>
#include <string.h>
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
    PGresult* res;
    conn = PQconnectdb("dbname=steer_main host=172.18.1.82 user=postgres password=terrm1nator");
    if (PQstatus(conn) == CONNECTION_BAD) {
        puts("We were unable to connect to the database");
        return 1;
    }
    //"
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
    if(iter==9){ iter=0;
        for(int i=0; i<sizeof(massln);i++){}
        char* pntr_date=(char*)massln[i].date.c_str();
        char* pntr_number=(char*)massln[i].number.c_str();
        char* pntr_number_2=(char*)massln[i].number_2.c_str();
        char* pntr_number_3=(char*)massln[i].number_3.c_str();
        char* pntr_duration=(char*)massln[i].call_duration.c_str();
        char* pntr_res=(char*)massln[i].res.c_str();
        const char* paramValues[6]={ (char*)pntr_date,(char*)pntr_number,(char*)pntr_number_2,(char*)pntr_number_3,(char*)pntr_duration,(char*)pntr_res};
        res=PQexecParams(conn,
                         "INSERT INTO steer.eir_test (date, number_first, number_second, number_third, call_duration, result) VALUES($1,$2,$3,$4,$5,$6)",
                         6,
                         NULL,
                         paramValues,
                         NULL,
                         NULL,
                         1);
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
            PQclear(res);
            return 2;
        }
        PQclear(res);
    }
    }
    fclose(file);
    PQfinish(conn);
    return 0;
}
