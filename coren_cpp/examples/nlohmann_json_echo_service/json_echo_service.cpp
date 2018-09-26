/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: yurik
 *
 * Created on 20 июля 2017 г., 15:27
 */

#include <cstdlib>

#include <iostream>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "Interface.h"
#include "JSON_Service.hpp"

using namespace CoreN;

namespace Json {

char Label[] = "application/json";

class Svc : public JSON_Service_Type(Label)
{
public:
    Svc(const InterfacePtr& I, const Service::Name& svc_name, int svc_pri)
        : JSON_Service_Type(Label)(I), name(svc_name), priority(svc_pri)
    {
        I->Register(name, priority, [this](const CoreN::Error& error, Service::Role role, const boost::shared_ptr<Service::Address>& master){
            std::cout << "Service " << name << " registred " << error << " as " << Utils::RoleToString(role);
            if (role == Service::Slave) {
                std::cout << " of " << *master;
            }
            std::cout << std::endl;
        }, Service::Detect);
    }

    void DefaultMessageHandler(const SessionTPtr& sess, const CoreN::Error& error, const MessagePtr& body, Session::Flags flags)
    {
        if (error || !body) {
            log_error("Start up with error O_o " << error);
            return;
        }

        std::cout << "Recv JOSN:" << dump(body) << " with sid:\"" << sess->Id() << "\"" << std::endl;
        if (flags == Session::Start) {
            stop(sess, body);
        } else {
            send(sess, body);
        }
    }

private:
    Service::Name name;
    int priority;
};

}

void on_connect(const InterfacePtr& I)
{
    auto echo_svc = boost::dynamic_pointer_cast<Service::Base>(
        boost::make_shared<Json::Svc>(I, "Echo", 100)
    );
    I->AddService(Json::Label, echo_svc);
}

int main()
{
    boost::asio::io_service ios;
    InterfacePtr I = Interface::Create(ios, "/tmp/core_n");
    I->on_connect = boost::bind(&on_connect, I);
    ios.run();
    return 0;
}

