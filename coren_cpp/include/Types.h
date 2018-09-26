/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Types.h
 * Author: yurik
 *
 * Created on 20 июля 2017 г., 15:40
 */

#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <list>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/function.hpp>
#include <boost/variant.hpp>

namespace CoreN {

    namespace Node {
        typedef std::string Name;
    }

    namespace Connection {
        typedef int Name;
    }

    struct Error {

        enum {
            None = 0,
            Unexpected = 99,
            Transport = 100,
            Encode = 101,
            Validation = 102
        };

        int code;
        std::string message;

        operator bool() const;
    };

    extern const Error ValidationError;
    extern const Error UnexpectedError;
    extern const Error TransportError;
    extern const Error EncodeError;
    extern const Error NoError;

    namespace Session {

        typedef std::string Name;
        typedef int Flags;

        enum {
            None      = 0x00,
            Start     = 0x01,
            Stop      = 0x02,
            Flash     = 0x03,
            Redirect  = 0x04,
            LocalOnly = 0x08,
            LocalPref = 0x10
        };

        class Base;

        extern const Name EmptyId;

    }

    typedef boost::shared_ptr<Session::Base> SessionPtr;
    typedef boost::weak_ptr<Session::Base> SessionRef;

    namespace Service {

        typedef int Role;

        enum {
            Master = 0,
            Slave  = 1,
            Detect = 2
        };

        typedef std::string Name;
        typedef std::string Type;

        struct Address {
            Service::Name    service;
            Node::Name       node;
            Connection::Name connection;

            friend bool operator==(const Address& left, const Address& right);
        };

        class Base;

    }

    namespace Info {

        typedef int Type;

        enum {
            Route = 0,
            Node = 1,
            Session = 2,
            Clients = 3
        };

        typedef std::list< std::pair<Service::Address, int> > RouteTable;
        typedef boost::variant< nullptr_t, RouteTable, std::string > Data;

        typedef boost::function<void (const Error& error, Type type, const Data& data)> Callback;
    }

    typedef boost::shared_ptr<Service::Base> ServicePtr;
    typedef boost::weak_ptr<Service::Base> ServiceRef;

    class Interface;
    typedef boost::shared_ptr<Interface> InterfacePtr;
    typedef boost::weak_ptr<Interface> InterfaceRef;

    class VirtualService;
}

#endif /* TYPES_H */
