#include "parser.h"

parser::parser()
{
}

vector<string> split(string str,const char * delimitr)
{
    std::vector<string> v;
    char* chars_array = strtok((char*)str.c_str(), delimitr);
    while(chars_array)
    {
        v.push_back(chars_array);
        chars_array = strtok(nullptr, delimitr);
    }
    return v;
}

void parser::transform_to_timestamp_promat(vector<vector<std::string> >* mass_ln_to_transform, int num_row){
    for(int i=0;i<mass_ln_to_transform->size();i++){
        std::string str_tr=mass_ln_to_transform->at(i).at(num_row);
        std::string timestamp=str_tr.substr(0,4)+"-"+str_tr.substr(4,2)+"-"+str_tr.substr(6,2)+" "+str_tr.substr(8,2)+":"+str_tr.substr(10,2)+":"+str_tr.substr(12,2);
        mass_ln_to_transform->at(i).at(num_row)=timestamp;
    }
}

vector<vector<std::string> > parser::pars_file(std::string fileName, int data_num, int start_reading_line){
    vector<vector<std::string> > rows;
    FILE* file;
    char* nameFile=(char*)fileName.c_str();
    file=fopen(nameFile,"r");
    if(file == NULL)
    {
        return rows;
    }
    for(int i=1; i<start_reading_line;i++)
    {
        char buf[1000];
        fgets(buf,1000,file);
    }
    while(!feof(file))
    {
        char buf[1000];
        fgets(buf,1000,file);
        if(strlen(buf)==0)
        {
            break;
        }
        std::string s1(buf);
        memset(buf,0,1000);
        char delimiter;
        delimiter=';';
        vector<std::string> row=split(s1,&delimiter);
        if(row.size()<data_num){
            std::string broke_row;
            int i=0;
            while(i<row.size()-1){
                broke_row+=row.at(i)+",";
                i++;
            }
            broke_row+=row.at(i);
            mass_broken_ln.push_back(broke_row);
        }
        else{
           rows.push_back(row);
           row.clear();
        }
    }
    fclose(file);
    return rows;
}
