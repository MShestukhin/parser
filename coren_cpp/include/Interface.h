/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Interface.h
 * Author: yurik
 *
 * Created on 20 июля 2017 г., 15:28
 */

#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include <list>
#include <map>

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/variant.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/optional.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/none.hpp>

#include "Types.h"

#ifndef _Message_H_
struct Message;
#endif

#ifndef ASN_AUTOEXPAND_BUFFER_H
struct asn_autoexpand_buffer_t;
#endif

namespace CoreN {

class Interface
    : public boost::noncopyable,
      public boost::enable_shared_from_this<Interface>
{
    Interface(boost::asio::io_service& ios_, const std::string& path_, int reconnect_timeout_);
public:
    static InterfacePtr Create(boost::asio::io_service& ios_, const std::string& path_, int reconnect_timeout_ = 1);
    virtual ~Interface();

private: // Network
    typedef boost::shared_ptr<Message> MessagePtr;

    boost::asio::io_service& ios;
    boost::asio::strand strand;
    boost::asio::local::stream_protocol::socket socket;
    boost::asio::deadline_timer reconnect_timer;
    boost::asio::local::stream_protocol::endpoint endpoint;
    boost::posix_time::time_duration reconnect_timeout;
    bool disconnected;
    bool connected;
    bool sending;

    std::list<MessagePtr> send_queue;

    boost::array<char, 1500> recv_buffer;
    boost::shared_ptr<asn_autoexpand_buffer_t> recv_asn_buffer;
    boost::shared_ptr<asn_autoexpand_buffer_t> send_asn_buffer;
    Message* current_decode_msg;

    void start_connect();
    void callback_connect(const boost::system::error_code& error);

    void start_receive();
    void callback_receive(const boost::system::error_code& error,
        size_t bytes_transferred);

    void start_timer();
    void callback_timer(const boost::system::error_code& error);

    void start_send();
    void callback_send(const boost::system::error_code& error);

    void send(const MessagePtr& msg, const SessionPtr& sess, Session::Flags flags);
    void clear_current_message();
    void close();

private:
    std::map< Session::Name, SessionRef > session_map;
    std::map< Service::Type, ServicePtr > service_map;

private:
    void Track(const SessionPtr& sess);
    void UnTrack(const SessionPtr& sess);
    SessionPtr FindSession(const Session::Name& sid) const;
    void ClearSessions();
    void CloseSession(const SessionPtr& sess, const Error& e);
    const ServicePtr& FindService(const Service::Name& label) const;
    void ErrorHandler(const Error& e, const Session::Name& sid);
    void MessageHandler(const MessagePtr& msg);
    MessagePtr MakeMessage();
    bool Idle() const;

    friend VirtualService;

public:
    void SendMessage(
        const SessionPtr& sess,
        const std::string& body,
        Session::Flags flags = Session::None,
        const boost::optional<boost::chrono::milliseconds>& timeout = boost::none
    );

    void AddService(const Service::Type& label, const ServicePtr& service);

    typedef boost::function<void (const Error& error, Service::Role role,
        const boost::shared_ptr<Service::Address>& master)> RegisterCallback;

    void Register(const Service::Name& svc_name, int svc_priority,
        RegisterCallback handler, Service::Role role = Service::Master);

    void UnRegister(const Service::Name& svc_name, RegisterCallback handler);

    void Info(Info::Callback handler, Info::Type type = Info::Route);

    void Disconnect();

private:
    void RegisterHelper(const Error& error, Info::Type type, const Info::Data& data,
        const Service::Name& svc_name, int svc_priority, RegisterCallback handler);

public:
    boost::function<void ()> on_connect;
    boost::function<void ()> on_disconnect;
    boost::function<void ()> on_idle;
};

}

#endif /* INTERFACE_H */
