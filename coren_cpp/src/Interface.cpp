/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Interface.cpp
 * Author: yurik
 *
 * Created on 20 июля 2017 г., 15:28
 */

// Sequence of headers is importatnt
// because of type forward declaration
// struct Message_t;
// struct asn_autoexpand_buffer_t;
#include <Message.h>
#include <asn_autoexpand_buffer.h>

#include "Interface.h"
#include "Service.h"
#include "Session.h"
#include "Utils.h"
#include "logger.h"
#include "asn_utils.h"
#include "VirtualService.h"

#define MAX_COUNT_MESSAGES_FOR_WRITE 100

namespace CoreN {

Interface::Interface(boost::asio::io_service& ios_, const std::string& path_, int reconnect_timeout_)
:   ios(ios_),
    strand(ios),
    socket(ios),
    reconnect_timer(ios),
    endpoint(path_),
    reconnect_timeout(boost::posix_time::seconds(reconnect_timeout_)),
    disconnected(false),
    connected(false),
    sending(false)
{
    current_decode_msg = NULL;
}

InterfacePtr Interface::Create(boost::asio::io_service& ios_, const std::string& path_, int reconnect_timeout_)
{
    InterfacePtr I(new Interface(ios_, path_, reconnect_timeout_));
    auto virtual_service = boost::make_shared<VirtualService>(I);
    I->AddService(
        virtual_service_label,
        boost::dynamic_pointer_cast<Service::Base>(virtual_service)
    );
    I->start_connect();
    return I;
}

Interface::~Interface() {
    clear_current_message();
}

void Interface::start_connect()
{
    socket.async_connect(
        endpoint,
        strand.wrap(
            boost::bind(
                &Interface::callback_connect,
                shared_from_this(),
                boost::asio::placeholders::error
            )
        )
    );
}

void Interface::callback_connect(const boost::system::error_code &error)
{
    if (error) {
        log_error("Error CoreN connect: " << error.message());
        socket.close();

        //запускаем таймер попытки соединения
        start_timer();
    } else {
        connected = true;

        send_asn_buffer.reset();
        recv_asn_buffer.reset();

        clear_current_message();

        start_receive();

        if (on_connect) {
            on_connect();
        }
    }
}

void Interface::start_receive()
{
    // Старт асинхронного чтения
    socket.async_read_some(
        boost::asio::buffer(recv_buffer),
        strand.wrap(
            boost::bind(
                &Interface::callback_receive,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        )
    );
}

void Interface::callback_receive(const boost::system::error_code &error, size_t bytes_transferred)
{
    if (error) {
        log_error("CoreN read error: " << error.message());
        recv_asn_buffer.reset();
        clear_current_message();
        close();
        return;
    }

    if (!connected) {
        return;
    }

    // Проверка что буфер для приёма живой
    if (!recv_asn_buffer) {
        recv_asn_buffer.reset(alloc_ae_buffer(1024), &free_ae_buffer);
    }

    // Перенос данных из приёмного буффера в буфер сообщения
    encode_to_ae_buffer_cb(recv_buffer.c_array(),
        bytes_transferred, recv_asn_buffer.get());

    while (1)
    {
        asn_dec_rval_t rval;
        rval = ber_decode(0, &asn_DEF_Message,
            reinterpret_cast<void**> (&current_decode_msg),
            recv_asn_buffer->buffer,
            size_ae_buffer(recv_asn_buffer.get()));

        if (rval.code != RC_FAIL) {
            // Сообщение распаковано успешно или частично

            // Удалить бинарные данные потреблённые из приёмного буффера
            shift_head_ae_buffer(recv_asn_buffer.get(), rval.consumed);

            //Сообщение декодировано полносью
            if (rval.code == RC_OK) {
                // Проверим все ли в сообщение правильно
                char errbuf[528];
                size_t errlen = sizeof(errbuf);
                if (asn_check_constraints(&asn_DEF_Message, current_decode_msg, errbuf, &errlen)) {
                    log_error("Constraint validation failed: " << errbuf);
                } else {
                    // Обработать полученное сообщение
                    MessagePtr m(current_decode_msg,
                        boost::bind(asn_DEF_Message.free_struct, &asn_DEF_Message, _1, ASFM_FREE_EVERYTHING)
                    );
                    current_decode_msg = NULL;
                    MessageHandler(m);
                }
            } else {
                // rval.code == RC_WMORE
                break; // while(1)
            }
        } else {
            // Сообщение распаковать не удалось

            // очищаем структуру
            clear_current_message();

            // Данные уже декодировать не удастся - рвем соединение
            log_error("Error decoding message, bad data");
            close();
            return;
        }
    }

    // Старт асинхронного чтения
    start_receive();
}

void Interface::start_timer()
{
    reconnect_timer.expires_from_now(reconnect_timeout);
    reconnect_timer.async_wait(
        strand.wrap(
            boost::bind(
                &Interface::callback_timer,
                shared_from_this(),
                boost::asio::placeholders::error
            )
        )
    );
}

void Interface::callback_timer(const boost::system::error_code &error)
{
    if (error) {
        log_error("Error reconnect timer: " << error.message());
    }
    if (!disconnected) {
        start_connect();
    }
}

void Interface::start_send()
{
    if (send_queue.empty() || sending) {
        return;
    }

    send_asn_buffer.reset(alloc_ae_buffer(1024), &free_ae_buffer);
    if (!send_asn_buffer) {
        log_error("Can't alloc output buffer");
        return;
    }
    bool there_is_send_data = false;

    for(size_t i = 0; (i < MAX_COUNT_MESSAGES_FOR_WRITE) && !send_queue.empty(); ++i) {
        char errbuf[528];
        size_t errlen = sizeof(errbuf);
        int ret = asn_check_constraints(&asn_DEF_Message, send_queue.front().get(), errbuf, &errlen);
        if(ret) {
            log_error("Constraint validation failed: " << errbuf);
            ErrorHandler(CoreN::EncodeError, asn1::cast::asnUTF8StringToString(send_queue.front()->sid));
        } else {
            asn_enc_rval_t err = der_encode(&asn_DEF_Message, send_queue.front().get(), encode_to_ae_buffer_cb, send_asn_buffer.get());
            if (err.encoded == -1) {
                log_error("Can't encode \"" << err.failed_type->name << "\" " << strerror(errno));
                ErrorHandler(ValidationError, asn1::cast::asnUTF8StringToString(send_queue.front()->sid));
            } else {
                //all success
                there_is_send_data = true;
            }
        }
        send_queue.erase(send_queue.begin());
    }

    if (there_is_send_data) {
        //были сообщения на отправку
        sending = true;
        boost::asio::async_write(
            socket,
            boost::asio::buffer(send_asn_buffer->buffer, size_ae_buffer(send_asn_buffer.get())),
            strand.wrap(
                boost::bind(
                    &Interface::callback_send,
                    shared_from_this(),
                    boost::asio::placeholders::error
                )
            )
        );
    }

    if (Idle() && on_idle) {
        on_idle();
    }
}

void Interface::callback_send(const boost::system::error_code &error)
{
    sending = false;
    if (error) {
        log_error("CoreN write error: " << error.message());
        send_asn_buffer.reset();
        close();
        return;
    }

    if(!connected) {
        return;
    }

    start_send();
}

void Interface::send(const MessagePtr& msg, const SessionPtr& sess, Session::Flags flags)
{
    if (flags & Session::Start) {
        Track(sess);
    }
    
    if (flags & (Session::Stop | Session::Redirect)) {
        UnTrack(sess);
    }

    if (!connected) {
        ErrorHandler(TransportError, asn1::cast::asnUTF8StringToString(msg->sid));
        return;
    }
    send_queue.push_back(msg);
    start_send();
}

void Interface::clear_current_message()
{
    if (current_decode_msg) {
        asn_DEF_Message.free_struct(&asn_DEF_Message, current_decode_msg, ASFM_FREE_EVERYTHING);
        current_decode_msg = NULL;
    }
}

void Interface::close()
{
    if (!connected) {
        return;
    }

    socket.close();

    sending = false;
    connected = false;

    clear_current_message();

    while (!send_queue.empty()) {
        auto it = send_queue.front();
        ErrorHandler(TransportError, asn1::cast::asnUTF8StringToString(it->sid));
        send_queue.pop_front();
    }

    ClearSessions();

    if (on_disconnect) {
        on_disconnect();
    }

    //запускаем таймер попытки соединения
    if (!disconnected) {
        start_timer();
    }
}

void Interface::Track(const SessionPtr& sess)
{
    const Session::Name& sid = sess->Id();
    session_map[sid] = SessionRef(sess);
    //log_debug("Track(\"" << sid << "\")");
}

void Interface::UnTrack(const SessionPtr& sess)
{
    const Session::Name& sid = sess->Id();
    session_map.erase(sid);
    //log_debug("UnTrack(\"" << sid << "\")");
    if (Idle() && on_idle) {
        on_idle();
    }
}

void Interface::ClearSessions()
{
    auto it = session_map.begin();
    while(it != session_map.end()) {
        const SessionRef& sess_ref = it->second;
        if (!sess_ref.expired()) {
            CloseSession(sess_ref.lock(), TransportError);
        } else {
            log_error("Session " << it->first << " disappeared unexpectedly.");
        }
        it = session_map.erase(it);
    }
}

void Interface::CloseSession(const SessionPtr& sess, const Error& e)
{
    const ServicePtr& service = FindService(sess->Label());
    if (service) {
        service->MessageHandler(sess, e, std::string(), Session::Stop);
    } else {
        log_error("Error on session id: " << sess->Id() << " with undefined service type: \"" << sess->Label() << "\"");
    }
}

SessionPtr Interface::FindSession(const Session::Name& sid) const
{
    static const SessionPtr empty;
    auto it = session_map.find(sid);
    if (it != std::end(session_map)) {
        const SessionRef& sess_ref = it->second;
        if (!sess_ref.expired()) {
            return sess_ref.lock();
        } else {
            log_error("Session " << sid << " disappeared unexpectedly.");
            return empty;
        }
    } else {
        return empty;
    }
}

const ServicePtr& Interface::FindService(const Service::Name& label) const
{
    static const ServicePtr empty;
    auto it = service_map.find(label);
    if (it != std::end(service_map)) {
        const ServicePtr& service = it->second;
        return service;
    } else {
        return empty;
    }
}

void Interface::ErrorHandler(const Error& e, const Session::Name& sid)
{
    const SessionPtr& sess = FindSession(sid);
    if (sess) {
        UnTrack(sess);
        CloseSession(sess, e);
    } else {
        log_error("Error on untracked session id: " << sid << " " << e);
    }
}

void Interface::MessageHandler(const MessagePtr& msg)
{
    const Session::Name& sid = asn1::cast::asnUTF8StringToString(msg->sid);
    const std::string& body = asn1::cast::asnUTF8StringToString(msg->body);
    int flags = asn1::cast::asnINTEGERToInt(&msg->flags);

    if (const SessionPtr& sess = FindSession(sid)) {
        if (flags == Session::Stop) {
            UnTrack(sess);
        }
        const ServicePtr& service = FindService(sess->Label());
        if (service) {
            service->MessageHandler(sess, CoreN::NoError, body, flags);
        } else {
            log_error("Message for unserved session id:" << sid << ". Message dropped.");
        }
    } else {
        const Service::Type& label = asn1::cast::asnUTF8StringToString(msg->label);
        const Service::Address& addr = Utils::Address(msg->src);
        if (!label.empty()) {
            const ServicePtr& service = FindService(label);
            if (service) {
                const SessionPtr& sess = service->MakeSession(addr, (sid.empty() ? Session::EmptyId : sid));
                if (sess) {
                    if (!sid.empty() && flags == Session::Start) {
                        Track(sess);
                    }
                    service->MessageHandler(sess, CoreN::NoError, body, flags);
                } else {
                    log_error("Service can't allocate session. Message dropped.");
                }
            } else {
                log_error("Unknown Service Type label: \"" << label << "\" from: " << addr << " sid: \"" << sid << "\". Message dropped.");
            }
        } else {
            log_error("No Service Type label from: " << addr << " sid: \"" << sid << "\". Message dropped.");
        }
    }
}

Interface::MessagePtr Interface::MakeMessage()
{
    MessagePtr msg(
        reinterpret_cast<Message*>(malloc(sizeof(Message))),
        boost::bind(asn_DEF_Message.free_struct, &asn_DEF_Message, _1, ASFM_FREE_EVERYTHING)
    );
    if (!msg) {
        static const char error_msg[] = "Can't allocate CoreN Message";
        log_error(error_msg);
        throw std::logic_error(error_msg);
    }
    memset(msg.get(), 0, sizeof (Message));
    return msg;
}

void Interface::SendMessage(const SessionPtr& sess, const std::string& body,
    Session::Flags flags, const boost::optional<boost::chrono::milliseconds>& timeout)
{
    MessagePtr msg = MakeMessage();

    // Заполняем тело сообщения
    if (!body.empty()) {
        asn1::cast::dataToAsnOCTET_STRING(&msg->body, body.data(), body.size());
    }

    // Заполнение адреса, куда отправляем
    if (!sess->Addr().service.empty()) {
        asn1::cast::stringToAsnUTF8String(&msg->dst.svcname, sess->Addr().service);
    }
    if (!sess->Addr().node.empty()) {
        asn1::cast::stringToAsnUTF8String(&msg->dst.hostname, sess->Addr().node);
    }
    if (sess->Addr().connection) {
        asn1::cast::intToAsnINTEGER(&msg->dst.svcconn, sess->Addr().connection);
    }

    // Заполнение локального сервиса
    if (!sess->LocalServiceName().empty()) {
        asn1::cast::stringToAsnUTF8String(&msg->src.svcname, sess->LocalServiceName());
    }

    // Заполняем метку
    if (!sess->Label().empty()) {
        asn1::cast::stringToAsnUTF8String(&msg->label, sess->Label());
    }

    // Заполняем идентификатор сессии
    if (!sess->Id().empty()) {
        asn1::cast::stringToAsnUTF8String(&msg->sid, sess->Id());
    }

    if (flags != Session::None) {
        asn1::cast::intToAsnINTEGER(&msg->flags, flags);
    }

    if (timeout) {
        const boost::chrono::microseconds& us_tmo = *timeout;
        asn1::cast::longToAsnINTEGER(&msg->tmo, us_tmo.count());
    }

    strand.post(boost::bind(&Interface::send, shared_from_this(), msg, sess, flags));
}

void Interface::AddService(const Service::Type& label, const ServicePtr& service)
{
    //log_debug("AddService(" << label << ")");
    service_map.emplace(
        label, service
    );
}

void Interface::Register(const Service::Name& svc_name, int svc_priority, RegisterCallback handler, Service::Role role)
{
    if (role == Service::Master) {
        auto service = boost::dynamic_pointer_cast<VirtualService>(
            FindService(virtual_service_label)
        );
        service->SetSvcName(svc_name, svc_priority,
            boost::bind(handler, _1, Service::Master,
                boost::shared_ptr<Service::Address>()
            )
        );
    } else {
        Info(boost::bind(&Interface::RegisterHelper, this, _1, _2, _3,
                svc_name, svc_priority, handler), Info::Route);
    }
}

void Interface::RegisterHelper(const Error& error, Info::Type type, const Info::Data& data,
    const Service::Name& svc_name, int svc_priority, RegisterCallback handler)
{
    if (error || type != Info::Route) {
        if (handler) {
            handler(error, Service::Master,
                boost::shared_ptr<Service::Address>());
        }
        return;
    }

    Info::RouteTable route_table;
    {
        const Info::RouteTable& rt = boost::get<Info::RouteTable>(data);
        std::copy_if(
            std::begin(rt),
            std::end(rt),
            std::back_inserter(route_table),
            [&svc_name](const std::pair<Service::Address, int> & record) {
                return record.first.service == svc_name;
            }
        );
    }

    route_table.sort([](const std::pair<Service::Address, int> & a, 
			const std::pair<Service::Address, int> & b){
        return a.second < b.second;
    });

    auto service = boost::dynamic_pointer_cast<VirtualService>(
        FindService(virtual_service_label)
    );
    if (route_table.empty()) {
        service->SetSvcName(svc_name, svc_priority,
            boost::bind(handler, _1, Service::Master,
                boost::shared_ptr<Service::Address>()
            )
        );
    } else {
        auto& master = route_table.front();
        auto& slave = route_table.back();
        service->SetSvcName(svc_name, std::max(slave.second + 10, svc_priority),
            boost::bind(handler, _1, Service::Slave,
                boost::make_shared<Service::Address>(master.first)
            )
        );
    }
}

void Interface::UnRegister(const Service::Name& svc_name, RegisterCallback handler)
{
    auto service = boost::dynamic_pointer_cast<VirtualService>(
        FindService(virtual_service_label)
    );
    service->SetSvcName(svc_name, -1,
        boost::bind(handler, _1, Service::Detect,
            boost::shared_ptr<Service::Address>()
        )
    );
}

void Interface::Info(Info::Callback handler, Info::Type type)
{
    auto service = boost::dynamic_pointer_cast<VirtualService>(
        FindService(virtual_service_label)
    );
    service->Info(handler, type);
}

bool Interface::Idle() const
{
    return session_map.empty() && send_queue.empty() && !sending;
}

void Interface::Disconnect()
{
    strand.post([this](){
        disconnected = true;
        if (!connected) {
            reconnect_timer.cancel();
        }
        if (socket.is_open()) {
            socket.shutdown(boost::asio::local::stream_protocol::socket::shutdown_send);
        }
    });
}

}
