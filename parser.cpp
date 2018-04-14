#include "parser.h"

parser::parser()
{
    mass_broken_ln=new vector<vector<std::string> >;
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
    vector<std::string> row;
    FILE* file;
    char* nameFile=(char*)fileName.c_str();
    file=fopen(nameFile,"r");
    if(file == NULL)
    {
        return rows;

    }
    for(int i=1; i<start_reading_line;i++){
    char buf[100];
    fgets(buf,100,file);
    }

    while(!feof(file)){
    char buf[100];
    fgets(buf,100,file);
    if(strlen(buf)==0){
        break;
    }
    std::string s1(buf);
    char delimiter;
    std::string::size_type n = s1.find(",");
    if ( n != std::string::npos )
    {
        delimiter=',';
    }
    else{
        delimiter=';';
    }
    int j=0;
    int i=0;
    int end=0;
    while(i<fileName.size()){
        if(fileName.at(i)==delimiter){
            std::string str=fileName.substr(end,i-end);
            row.push_back(str);
            end=i+1;
            j++;
        }
        i++;
    }
    std::string str=fileName.substr(end,i-end);
    row.push_back(str);
    if(j<data_num){
        mass_broken_ln->push_back(row);
    }
    else{
       rows.push_back(row);
    }
    }
    fclose(file);
    return rows;
}
