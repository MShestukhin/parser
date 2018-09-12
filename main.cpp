#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "working_file.h"
#include "parser.h"
#include <boost/thread.hpp>
#include "CNora.h"
#include "worker_cnora.h"
using boost::property_tree::ptree;
using namespace std;
string from_pth;
string work_pth;
string done_pth;
string log_pth;
string src_fl;
string db_schema;
string db_table;
vector<string> table_name;
vector<string> table_type;

void init(){
    std::ifstream file;
    file.open("/opt/svyazcom/etc/cdr.conf");
    if(!file.is_open())
        log_error("Error open config file");
    ptree pt;
    try {
        read_json(file, pt);
        src_fl=pt.get<string>("paths.sourceFile");
        from_pth=pt.get<string>("paths.sourceDir");
        work_pth=pt.get<string>("paths.uploadDir");
        done_pth=pt.get<string>("paths.workOutDir");
        log_pth=pt.get<string>("paths.logDir");

        //database
        for(boost::property_tree::ptree::value_type &v : pt.get_child("tableName"))
            table_name.push_back( v.second.data());
        for(boost::property_tree::ptree::value_type &v : pt.get_child("tableType"))
            table_type.push_back( v.second.data());
        db_schema=pt.get<string>("dataBase.schema");
        db_table=pt.get<string>("dataBase.table");

    } catch (boost::property_tree::json_parser::json_parser_error &je) {
        log_error( "Error parsing: " << je.filename() << " on line: " << je.line());
        log_error( je.message());
    }
    file.close();
}

boost::asio::io_service io;
Worker_cnora cnora(io);

void on_signal(const boost::system::error_code& error, int signal_number)
{
    if (error) {
        log_error("Signal with error :"<<error.message());
    }
    log_info("Got signal "<<signal_number<<":"<<strsignal(signal_number));
    cnora.stop();
}

void mainThread(){
    while(1){
        sleep(5);
        string format="";
        transport_file(format,from_pth,work_pth,src_fl,contains);
        vector<Working_file> upload_file=file_lookup(work_pth,src_fl,contains);
        for(auto ff : upload_file){
            string file_name=ff.name;
            parser Parser;
            vector<vector<std::string> > rows=Parser.pars_file(file_name,table_name.size(),2);
            Parser.transform_to_timestamp_promat(&rows,0);
            cnora.multiple_insertDb(rows,db_schema,db_table,table_name,table_type);
            string format="done_";
            transport_file(format,work_pth,done_pth,src_fl,contains);
        }
    }
}

int main()
{
    init();
    boost::thread thread(&mainThread);
    boost::asio::signal_set signals(io, SIGINT, SIGTERM);
    signals.async_wait(
        boost::bind(&on_signal, _1, _2)
    );
    boost::system::error_code error;
    io.run(error);
    thread.join();
    if (error) {
        log_error("ios.run() error: " << error.message());
    }
    log_debug("ios thread terminated");
    return 0;
}
