/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   JSON_Service.h
 * Author: Yury Bogachev
 *
 * Created on 20 июля 2017 г., 15:31
 */

#ifndef JSON_SERVICE_H
#define JSON_SERVICE_H

#include <exception>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/optional.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/swap.hpp>
#include <boost/none.hpp>

#include "Interface.h"
#include "Service.h"
#include "Session.h"

#include <json.hpp>
#include "logger.h"
#include "Utils.h"

namespace CoreN {

namespace Service {

template <
    char * const Label
>
class JSON_Template : public Service::Base
{
public:
    using json = nlohmann::json;
    typedef boost::shared_ptr<json> MessagePtr;
    typedef boost::function<void (const Error& error, const MessagePtr& body, Session::Flags flags)> MessageHandlerT;

    JSON_Template(const InterfacePtr& interface_)
        : coren_if(interface_)
    {
    }

    virtual ~JSON_Template()
    {
    }

    class SessionT : public Session::Base
    {
    public:
        SessionT(const Service::Type& label_, const Service::Address& remote_, const Session::Name& id_)
            : Session::Base(label_, remote_, id_)
        {
        }
        MessageHandlerT on_message;
    };
    typedef boost::shared_ptr<SessionT> SessionTPtr;

    SessionPtr MakeSession(const Service::Address& remote, const Session::Name& sid = "")
    {
        return boost::dynamic_pointer_cast<Session::Base>(NewSession(remote, sid));
    }

    SessionTPtr NewSession(const Service::Address& remote, const Session::Name& sid = "")
    {
        return boost::make_shared<SessionT>(Label, remote, sid);
    }

    MessagePtr MakeMessage()
    {
        return boost::make_shared<json>();
    }

    virtual void DefaultMessageHandler(const SessionTPtr& sess,
            const Error& error, const MessagePtr& body, Session::Flags flags)
    {
        if (error) {
            log_error("CoreN Error " << error << " on session id:" << sess->Id());
            return;
        }
        log_error("Default Handler Implementation required. "
                "Unexpected incoming " << Label << " message: " << dump(body));
        if (flags & Session::Start) {
            const MessagePtr& ans = MakeMessage();
            stop(sess, ans);
        }
    }

    void MessageHandler(const SessionPtr& sess, const Error& error,
            const std::string& body, Session::Flags flags)
    {
        static const MessagePtr empty;
        const SessionTPtr& s = boost::dynamic_pointer_cast<SessionT>(sess);
        const MessagePtr& b = body.empty() ? empty : deserialization(body);
        if (s->on_message) {
            MessageHandlerT f;
            boost::swap(f, s->on_message);
            f(error, b, flags);
        } else {
            DefaultMessageHandler(s, error, b, flags);
        }
    }

    void start(const SessionTPtr& sess, const MessagePtr& body, MessageHandlerT handler_,
            const boost::optional<boost::chrono::milliseconds>& timeout = boost::none,
            Session::Flags flags = Session::None)
    {
        send(sess, body, Session::Start | flags, timeout);
        sess->on_message = handler_;
    }

    void stop(const SessionTPtr& sess, const MessagePtr& body)
    {
        send(sess, body, Session::Stop);
    }

    void send(const SessionTPtr& sess, const MessagePtr& body,
            Session::Flags flags = Session::None,
            const boost::optional<boost::chrono::milliseconds>& timeout = boost::none)
    {
        const std::string& buffer = serialization(body);
        coren_if->SendMessage(sess, buffer, flags, timeout);
    }

    void recv(const SessionTPtr& sess, MessageHandlerT handler_)
    {
        sess->on_message = handler_;
    }

    void redir(const SessionTPtr& sess, const MessagePtr& body,
            const Service::Address& to, Session::Flags flags = Session::None)
    {
        const Session::Name& sid = sess->Id();
        const Service::Type& label = sess->Label();
        sess.reset(boost::make_shared<SessionT>(label, to, sid));
        send(sess, body, Session::Redirect | flags);
    }

    static std::string dump(const MessagePtr& body)
    {
        return body->dump();
    }

    static std::string serialization(const MessagePtr& body)
    {
        return body->dump();
    }

    static MessagePtr deserialization(const std::string& body)
    {
        try {
            // static member can't call MakeMessage()
            const MessagePtr& p = boost::make_shared<json>();

            std::istringstream iss(body);
            iss >> *p;

            return p;
        } catch (std::exception &e) {
            log_error("Error decoding message: " << e.what());
        }
        return MessagePtr();
    }

protected:
    const InterfacePtr& coren_if;
};

}

}

#define JSON_Service_Type(LABEL) \
    ::CoreN::Service::JSON_Template<LABEL>

#endif /* JSON_SERVICE_H */
