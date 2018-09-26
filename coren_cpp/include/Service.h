/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Service.h
 * Author: yurik
 *
 * Created on 20 июля 2017 г., 15:29
 */

#ifndef SERVICE_H
#define SERVICE_H

#include <boost/noncopyable.hpp>
#include "Types.h"

namespace CoreN {

namespace Service {

class Base
    : private boost::noncopyable
{
public:
    virtual ~Base() = 0;

    virtual SessionPtr MakeSession(
        const Service::Address& remote,
        const Session::Name& sid = ""
    ) = 0;

    virtual void MessageHandler(
        const SessionPtr& sess,
        const Error& error,
        const std::string& body,
        Session::Flags flags
    ) = 0;
};

}

}

#endif /* SERVICE_H */
