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
#include "log.h"
using boost::property_tree::ptree;
using namespace std;
class log logg;
string from_pth;
string work_pth;
string done_pth;
string log_pth;
string src_fl;
string db_schema;
string db_table;
vector<string> table_name;
vector<string> table_type;
string coren_socket;
string cnora_name;

void init(){
    std::ifstream file;
    file.open("/opt/svyazcom/etc/cdr.conf");
    if(!file.is_open())
        logg.error("Error open config file");
    ptree pt;
    try {
        read_json(file, pt);
        src_fl=pt.get<string>("paths.sourceFile");
        from_pth=pt.get<string>("paths.sourceDir");
        work_pth=pt.get<string>("paths.uploadDir");
        done_pth=pt.get<string>("paths.workOutDir");
        log_pth=pt.get<string>("paths.logDir");
            logg.init(log_pth);
        //database
        for(boost::property_tree::ptree::value_type &v : pt.get_child("tableName"))
            table_name.push_back( v.second.data());
        for(boost::property_tree::ptree::value_type &v : pt.get_child("tableType"))
            table_type.push_back( v.second.data());

        db_schema=pt.get<string>("dataBase.schema");
        db_table=pt.get<string>("dataBase.table");

        coren_socket=pt.get<string>("cnora.coren_socket");
        cnora_name=pt.get<string>("cnora.cnora_name");

    } catch (boost::property_tree::json_parser::json_parser_error &je) {
        logg.error("Error parsing: " + je.filename() + " on line: " + to_string(je.line()));
        logg.error(je.message());
    }
    file.close();
}

boost::asio::io_service io;

void on_signal(const boost::system::error_code& error, int signal_number)
{
    if (error) {
        logg.error("Signal with error :"+error.message());
    }
    logg.error("Got signal "+to_string(signal_number)+":"+strsignal(signal_number));
    exit(1);
}

void iosThread(){
    boost::asio::signal_set signals(io, SIGINT, SIGTERM);
    signals.async_wait(
        boost::bind(&on_signal, _1, _2)
    );
    boost::system::error_code error;
    io.run(error);
    if (error) {
        logg.error("ios.run() error: " + error.message());
    }
    logg.error("ios thread terminated");
}

int main()
{
    init();
    boost::thread thread(&iosThread);
    Worker_cnora cnora(io);
    while(1){
        sleep(5);
        string format="";
        transport_file(format,from_pth,work_pth,src_fl,contains);
        vector<Working_file> upload_file=file_lookup(work_pth,src_fl,contains);
        for(auto ff : upload_file){
            string file_name=ff.name;
            logg.info("Begin work with "+file_name);
            parser Parser;
            vector<vector<std::string> > rows=Parser.pars_file(file_name,table_name.size(),2);
            if(Parser.mass_broken_ln.size()){
                logg.error("Find broke rows "+to_string(Parser.mass_broken_ln.size()));
            }
            logg.info(to_string(rows.size())+" lines to load into the database");
            Parser.transform_to_timestamp_promat(&rows,0);
            cnora.multiple_insertDb(rows,db_schema,db_table,table_name,table_type);
            string format="done_";
            transport_file(format,work_pth,done_pth,src_fl,contains);
        }
    }
    thread.join();
    return 0;
}
