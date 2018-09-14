#include "worker_cnora.h"
#include <iostream>
#include <plog/Log.h>
CoreN::InterfacePtr getCoreN(boost::asio::io_service& ios)
{
    const std::string& unix_socket_name = "/opt/svyazcom/var/run/coren.sock";
    unsigned int reconnect_tmo = 5;
    return CoreN::Interface::Create(ios, unix_socket_name, reconnect_tmo);
}

CoreN::CNoraPtr getCNora(const CoreN::InterfacePtr& I)
{
    const CoreN::Service::Address remote {
        "CNORA", "", 0
    };
    const boost::chrono::milliseconds timeout {
        1000
    };
    CoreN::CNoraPtr svc = boost::make_shared<CoreN::CNora>(I, remote, timeout);
    I->AddService(CoreN::cnora_label, boost::dynamic_pointer_cast<CoreN::Service::Base>(svc));
    return svc;
}

void rebind(boost::function<void()>& f, const boost::function<void(const boost::function<void()>& handler)>& new_one)
{
    boost::function<void()> origin;
    boost::swap(origin, f);
    f = [new_one, origin]() {
        new_one(origin ? origin : [](){});
    };
}

Worker_cnora::Worker_cnora(boost::asio::io_service& io)
{
    I = getCoreN(io);
    rebind(I->on_connect, [](const boost::function<void()>& handler){
        LOGI<<"Coren ready to work";
        handler();
    });
}

void Worker_cnora::stop(){
    I->UnRegister("", [](
            const CoreN::Error& error,
            CoreN::Service::Role /*role*/,
            const boost::shared_ptr<CoreN::Service::Address>& /*master*/
        ){
            LOGI<<"Service UnRegistered " << error;
        });
}

void Worker_cnora::insertDb(vector<vector<string>> data_ln, string db_schema, string db_table, vector<string> table_name, vector<string> table_type){
    //load tables data
    const CoreN::CNoraPtr& cnora=getCNora(I);
    CoreN::CNora::Values v;
    std::string insert_begin="INSERT INTO "+db_schema+"."+db_table+" (";
    std::string insert_end=") VALUES(";
    for(int i=0;i<table_name.size();i++)
    {
        insert_begin=insert_begin+table_name.at(i);
        insert_end=insert_end+"$"+to_string(i+1)+table_type.at(i);
        if((i+1)!=table_name.size())
        {
            insert_end+=",";
            insert_begin+=",";
        }
    }
    std::string insert_cmd_str=insert_begin+insert_end+")";
    for(int i=0;i<data_ln.size();i++){
        for(int j=0;j<data_ln.at(i).size();j++)
            v.emplace_back(CoreN::CNora::Value(data_ln.at(i).at(j)));
        cnora->Request(
            insert_cmd_str, // SQL
            v, // Binded params
            CoreN::CNora::Commit | CoreN::CNora::StopSession, // Some flags for request
                [](const CoreN::CNora::Rows& ) {},
                [](const CoreN::Error& error){
                    if(error!=0)
                        LOGE<< "Request status: " << error << std::endl;
                } // Method on request finish
        );
        v.clear();
    };
}

int Worker_cnora::multiple_insertDb(vector<vector<string>> data_ln, string db_schema, string db_table, vector<string> table_name, vector<string> table_type){
        const CoreN::CNoraPtr& cnora=getCNora(I);
        CoreN::CNora::Values v;
        std::string insert_begin="INSERT INTO "+db_schema+"."+db_table+" (";
        for(int i=0;i<table_name.size();i++)
        {
            insert_begin=insert_begin+table_name.at(i);
            if((i+1)!=table_name.size())
            {
                insert_begin+=",";
            }
        }
        std::string insert_end=") VALUES";
        for(auto  row : data_ln){
            string value="(";
            int n=row.size()-1;
            for(int i=0;i<n;i++){
                value+="'"+row.at(i)+"'"+table_type.at(i)+",";
            }
            insert_end+=value+row.at(n)+table_type.at(n)+"),";
        }
        insert_end=insert_end.erase(insert_end.size()-1,1);
        cnora->Request(
            insert_begin+insert_end, // SQL
            v, // Binded params
            CoreN::CNora::Commit | CoreN::CNora::StopSession, // Some flags for request
                [](const CoreN::CNora::Rows& ) {},
                [](const CoreN::Error& error){
                    if(error!=0)
                        LOGE << "Request status: " << error << std::endl;
                    else
                        LOGI<<"Success edit to database";
                } // Method on request finish
        );
        v.clear();
}
