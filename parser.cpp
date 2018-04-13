#include "parser.h"

parser::parser()
{
}

void parser::transform_to_timestamp_promat(char* newNumber,char* str){
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

int parser::pars_file(std::string file_name){
    FILE* file;
    char* nameFile=(char*)file_name.c_str();
    file=fopen(nameFile,"r");
    if(file == NULL)
    {
        printf("Can not open file");
        return 1;
    }
    char buf[100];
    fgets(buf,100,file);
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
        /*    vector<vector<std::string>> mass_ln;
    vector<std::string> data_ln;
    std::string fileName="20180405142432;2_file;79834077832;79500539520;9834077821";
    char* pointer=(char*)fileName.c_str();
    char* pointerBegin=pointer;
    int i=0;
    int end=0;
    while(i<fileName.size()){
        //std::cout<<fileName.at(i)<<"\n";
        if(fileName.at(i)==';'){
            std::string str=fileName.substr(end,i-end);
            data_ln.push_back(str);
            end=i+1;
        }
        i++;
    }
    std::string str=fileName.substr(end,i-end);
    data_ln.push_back(str);
    std::string str_tr=data_ln.at(0);
    std::string timestamp=str_tr.substr(0,4)+"-"+str_tr.substr(4,2)+"-"+str_tr.substr(6,2)+" "+str_tr.substr(8,2)+":"+str_tr.substr(10,2)+":"+str_tr.substr(12,2);
    std::cout<<timestamp;*/
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
                    break;
                case 6:
                    ln.res=new char[strlen(str)];
                    strcpy(ln.res,str);
                    break;
                default:
                    break;
                }
                i++;
            }
        }
    str[j-1]='\0';
    ln.resKey=new char[strlen(str)];
    strcpy(ln.resKey,str);
    if(i<7){
        return 2;
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
    return 0;
}
