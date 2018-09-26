/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Session.h
 * Author: yurik
 *
 * Created on 20 июля 2017 г., 15:29
 */

#ifndef SESSION_H
#define SESSION_H

#include <boost/noncopyable.hpp>
#include "Types.h"

namespace CoreN {

namespace Session {

class Base
    : private boost::noncopyable
{
public:
    Base(const Service::Type& label_, const Service::Address& remote_, const Session::Name& id_ = "", const Service::Name &local_service_="");

    virtual ~Base();

    const Session::Name& Id() const;
    const Service::Address& Addr() const;
    const Service::Type& Label() const;
    const Service::Name& LocalServiceName() const;
    void LocalServiceName(const Service::Name&);
protected:
    Service::Type    label;
    Service::Address remote;
    Session::Name    id;
    Service::Name    local_service;
};

}

}

#endif /* SESSION_H */
