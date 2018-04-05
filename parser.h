#ifndef PARSER_H
#define PARSER_H
#include "main.h"
class parser
{
private :
    void transform_to_timestamp_promat(char* newNumber,char* str);
public:
    parser();
    int pars_file(std::string file_name);
};

#endif // PARSER_H
