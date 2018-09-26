/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Session.cpp
 * Author: yurik
 *
 * Created on 20 июля 2017 г., 15:29
 */

#include "Session.h"
#include "Utils.h"

namespace CoreN {

namespace Session {

Base::Base(const Service::Type& label_, const Service::Address& remote_, const Session::Name& id_, const Service::Name &local_service_)
  : label(label_), remote(remote_), id(id_), local_service(local_service_)
{
    if (id.empty()) {
        id = Utils::GenerateId(label);
    }
}

Base::~Base() {
}

const Session::Name& Base::Id() const
{
    static Session::Name empty;
    if (id == Session::EmptyId) {
        return empty;
    } else {
        return id;
    }
}

const Service::Address& Base::Addr() const
{
    return remote;
}

const Service::Name& Base::LocalServiceName() const{
    return local_service;
}

void Base::LocalServiceName(const Service::Name& local_service_){
    local_service=local_service_;
}

const Service::Type& Base::Label() const
{
    return label;
}

}

}
