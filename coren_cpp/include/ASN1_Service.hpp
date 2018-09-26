/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ASN1_Service.h
 * Author: Yury Bogachev
 *
 * Created on 20 июля 2017 г., 15:30
 */

#ifndef ASN1_SERVICE_HPP
#define ASN1_SERVICE_HPP
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

#include "constr_TYPE.h"
#include <ber_decoder.h>
#include <der_encoder.h>
#include <xer_encoder.h>
#include <constraints.h>

#include "asn_utils.h"
#include "logger.h"
#include "Utils.h"

namespace CoreN {

namespace Service {

template <
    typename MsgPtr,
    asn_TYPE_descriptor_t* type_desc
>
std::string dump_tmpl(const MsgPtr& body)
{
    char errbuf[528];
    size_t errlen = sizeof(errbuf);

    if (asn_check_constraints(type_desc, body.get(), errbuf, &errlen) == 0) {
        std::string result;
        asn_enc_rval_t err = xer_encode(type_desc, body.get(), XER_F_BASIC,
                asn1::encode::string_buffer_cb, &result);
        if (err.encoded != -1) {
            return result;
        }
    }

    return std::string();
}

template <
    char * const Label,
    typename MsgTypeRecv,
    asn_TYPE_descriptor_t* type_desc_recv,
    typename MsgTypeSend = MsgTypeRecv,
    asn_TYPE_descriptor_t* type_desc_send = type_desc_recv
>
class ASN1_Template : public Service::Base
{
public:
    typedef boost::shared_ptr<MsgTypeRecv> RecvMessagePtr;
    typedef boost::shared_ptr<MsgTypeSend> SendMessagePtr;
    typedef boost::function<void (const Error& error, const RecvMessagePtr& body, Session::Flags flags)> MessageHandlerT;

    ASN1_Template(const InterfacePtr& interface_)
        : coren_if(interface_)
    {
    }

    virtual ~ASN1_Template()
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

    SendMessagePtr MakeMessage()
    {
        SendMessagePtr msg(
            reinterpret_cast<MsgTypeSend*>(malloc(sizeof(MsgTypeSend))),
            boost::bind(type_desc_send->free_struct, type_desc_send, _1, ASFM_FREE_EVERYTHING)
        );
        if (!msg) {
            static const char error_msg[] = "Can't allocate CoreN Message";
            log_error(error_msg);
            throw std::logic_error(error_msg);
        }
        memset(msg.get(), 0, sizeof (MsgTypeSend));
        return msg;
    }

    virtual void DefaultMessageHandler(const SessionTPtr& sess,
            const Error& error, const RecvMessagePtr& body, Session::Flags flags)
    {
        if (error) {
            log_error("CoreN Error " << error << " on session id:" << sess->Id());
            return;
        }
        log_error("Default Handler Implementation required. "
                "Unexpected incoming " << Label << " message: " << dump(body));
        if (flags & Session::Start) {
            const SendMessagePtr& ans = MakeMessage();
            stop(sess, ans);
        }
    }

    void MessageHandler(const SessionPtr& sess, const Error& error,
            const std::string& body, Session::Flags flags)
    {
        static const RecvMessagePtr empty;
        const SessionTPtr& s = boost::dynamic_pointer_cast<SessionT>(sess);
        const RecvMessagePtr& b = body.empty() ? empty : deserialization(body);
        if (s->on_message) {
            MessageHandlerT f;
            boost::swap(f, s->on_message);
            f(error, b, flags);
        } else {
            DefaultMessageHandler(s, error, b, flags);
        }
    }

    void start(const SessionTPtr& sess, const SendMessagePtr& body, MessageHandlerT handler_,
            const boost::optional<boost::chrono::milliseconds>& timeout = boost::none,
            Session::Flags flags = Session::None)
    {
        send(sess, body, Session::Start | flags, timeout);
        sess->on_message = handler_;
    }

    void stop(const SessionTPtr& sess, const SendMessagePtr& body)
    {
        send(sess, body, Session::Stop);
    }

    void send(const SessionTPtr& sess, const SendMessagePtr& body,
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

    void redir(const SessionTPtr& sess, const SendMessagePtr& body,
            const Service::Address& to, Session::Flags flags = Session::None)
    {
        const Session::Name& sid = sess->Id();
        const Service::Type& label = sess->Label();
        sess.reset(boost::make_shared<SessionT>(label, to, sid));
        send(sess, body, Session::Redirect | flags);
    }

    template<typename Q = RecvMessagePtr>
    static typename std::enable_if<std::is_same<Q, RecvMessagePtr>::value, std::string>::type dump(const Q& body)
    {
        return dump_tmpl<Q, type_desc_recv>(body);
    }

    template<typename Q = SendMessagePtr>
    static typename std::enable_if<!std::is_same<Q, RecvMessagePtr>::value, std::string>::type dump(const Q& body)
    {
        return dump_tmpl<Q, type_desc_send>(body);
    }

    static std::string serialization(const SendMessagePtr& body)
    {
        char errbuf[528];
        size_t errlen = sizeof (errbuf);

        if (asn_check_constraints(type_desc_send, body.get(), errbuf, &errlen) == 0) {
            std::string result;
            asn_enc_rval_t err = der_encode(type_desc_send, body.get(),
                    asn1::encode::string_buffer_cb, &result);
            if (err.encoded != -1) {
                return result;
            } else {
                log_error("Can't encode \"" << err.failed_type->name << "\" " << strerror(errno));
            }
        } else {
            log_error("Constraint validation failed: " << errbuf);
        }

        return std::string();
    }

    static RecvMessagePtr deserialization(const std::string& body)
    {
        MsgTypeRecv* msg = nullptr;

        asn_dec_rval_t rval = ber_decode(0, type_desc_recv,
            reinterpret_cast<void**> (&msg),
            body.data(), body.size()
        );

        RecvMessagePtr p(msg,
            boost::bind(type_desc_recv->free_struct, type_desc_recv, _1, ASFM_FREE_EVERYTHING));

        if (rval.code == RC_OK) {
            char errbuf[528];
            size_t errlen = sizeof(errbuf);
            if (asn_check_constraints(type_desc_recv, p.get(), errbuf, &errlen) == 0) {
                return p;
            } else {
                log_error("Constraint validation failed: " << errbuf);
            }
        } else {
            log_error("Error decoding message, bad data");
        }

        return RecvMessagePtr();
    }

protected:
    const InterfacePtr& coren_if;
};

}

}

#define ASN1_Service_Type(LABEL, MSG_TYPE) \
    ::CoreN::Service::ASN1_Template<LABEL, MSG_TYPE, &asn_DEF_ ## MSG_TYPE>

#define ASN1_Service_Complex_Type(LABEL, MSG_TYPE_RECV, MSG_TYPE_SEND) \
    ::CoreN::Service::ASN1_Template<LABEL, MSG_TYPE_RECV, &asn_DEF_ ## MSG_TYPE_RECV, MSG_TYPE_SEND, &asn_DEF_ ## MSG_TYPE_SEND>

#endif /* ASN1_SERVICE_HPP */
