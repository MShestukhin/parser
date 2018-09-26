#include <CoreNProtocol.h>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>

#define VIRTUAL_SERVICE_CPP 1
#include "VirtualService.h"
#include "Interface.h"

namespace CoreN {

VirtualService::VirtualService(const InterfacePtr& interface_)
  : ASN1_Service_Type(virtual_service_label, CoreNProtocol)(interface_)
{
}

void VirtualService::DefaultMessageHandler(const SessionTPtr& sess, const Error& error, const RecvMessagePtr& body, Session::Flags /*flags*/)
{
    if (error || !body) {
        log_error("Unexpected CoreN Error: " << error << " from " << sess->Addr() << ". Message dropped");
        return;
    }

    switch (body->present) {
        case CoreNProtocol_PR_errormsg: {
            CoreNError_t& m = body->choice.errormsg;
            const Session::Name& sid = asn1::cast::asnUTF8StringToString(&m.sid);
            const Error err {
                asn1::cast::asnINTEGERToInt(&m.errorcode),
                asn1::cast::asnUTF8StringToString(m.errormsg)
            };
            coren_if->ErrorHandler(err, sid);
            break;
        }
        default: {
            log_error("Unexpected CoreN Message: " << dump(body));
            break;
        }
    }
}

void VirtualService::SetSvcName(const Service::Name& svc_name, int svc_priority, SetSvcNameCallback handler)
{
    const auto& sess = NewSession(Remote());
    const auto& mess = MakeMessage();
    {
        mess->present = CoreNProtocol_PR_setsvcname;
        SetSvcName_t& req = mess->choice.setsvcname;
        asn1::cast::stringToAsnUTF8String(&req.svcname, svc_name);
        asn1::cast::intToAsnINTEGER(&req.priority, svc_priority);
    }
    start(sess, mess, boost::bind(&VirtualService::SetSvcNameResponse, this, sess, _1, _2, _3, handler));
}

void VirtualService::SetSvcNameResponse(const SessionTPtr& sess, const Error& error, const RecvMessagePtr& body, Session::Flags flags, SetSvcNameCallback handler)
{
    if (error || !body) {
        if (handler) {
            handler(error);
        }
        return;
    }

    if (!(flags & Session::Stop)) {
        coren_if->UnTrack(boost::dynamic_pointer_cast<Session::Base>(sess));
    }

    switch (body->present) {
        case CoreNProtocol_PR_errormsg: {
            CoreNError_t& m = body->choice.errormsg;
            const Session::Name& sid = asn1::cast::asnUTF8StringToString(&m.sid);
            const Error err {
                asn1::cast::asnINTEGERToInt(&m.errorcode),
                asn1::cast::asnUTF8StringToString(m.errormsg)
            };
            if (handler) {
                handler(err);
            }
            break;
        }
        default: {
            log_error("Unexpected CoreN Message: " << dump(body));
            if (handler) {
                handler(CoreN::UnexpectedError);
            }
            break;
        }
    }
}

void VirtualService::Info(Info::Callback handler, Info::Type type)
{
    const auto& sess = NewSession(Remote());
    const auto& mess = MakeMessage();
    {
        mess->present = CoreNProtocol_PR_info_request;
        CoreNInfoRequest_t& req = mess->choice.info_request;
        asn1::cast::intToAsnINTEGER(&req.code, type);
    }
    start(sess, mess, boost::bind(&VirtualService::InfoResponse, this, sess, _1, _2, _3, handler));
}

void VirtualService::InfoResponse(const SessionTPtr& sess, const Error& error, const RecvMessagePtr& body, Session::Flags flags, Info::Callback handler)
{
    static const Info::Type err_type = -1;
    static const Info::Data err_data = nullptr;
    if (error || !body) {
        if (handler) {
            handler(error, err_type, err_data);
        }
        return;
    }

    if (!(flags & Session::Stop)) {
        coren_if->UnTrack(boost::dynamic_pointer_cast<Session::Base>(sess));
    }

    switch (body->present) {
        case CoreNProtocol_PR_errormsg: {
            CoreNError_t& m = body->choice.errormsg;
            const Session::Name& sid = asn1::cast::asnUTF8StringToString(&m.sid);
            const Error err {
                asn1::cast::asnINTEGERToInt(&m.errorcode),
                asn1::cast::asnUTF8StringToString(m.errormsg)
            };
            if (handler) {
                handler(err, err_type, err_data);
            }
            break;
        }
        case CoreNProtocol_PR_info_response: {
            CoreNInfoResponse_t& m = body->choice.info_response;
            Info::Type type = asn1::cast::asnINTEGERToInt(&m.code);
            const std::string& info = asn1::cast::asnUTF8StringToString(&m.info);
            Info::Data data;
            switch (type) {
                case Info::Route: {
                    Info::RouteTable rt;
                    /*
                      Service GMSU-Cnora  Node N13080 Connection 2  Priority 0
                      Service GMSU-Router Node N13080 Connection 94 Priority 0
                    */
                    std::istringstream iss(info);
                    for (std::string line; std::getline(iss, line); ) {
                        boost::tuple<
                            std::string, std::string, // Service
                            std::string, std::string, // Node
                            std::string, int,         // Connection
                            std::string, int          // Priority
                        > rr;
                        {
                            line = "(" + line + ")";
                            std::istringstream lss(line);
                            lss >> rr;
                        }

                        Service::Address svc_addr {
                            rr.get<1>(), rr.get<3>(), rr.get<5>()
                        };
                        int svc_priority = rr.get<7>();

                        rt.emplace_back(
                            std::make_pair(svc_addr, svc_priority)
                        );
                    }
                    data = rt;
                    break;
                }
                default: {
                    data = info;
                    break;
                }
            }
            if (handler) {
                handler(error, type, data);
            }
            break;
        }
        default: {
            log_error("Unexpected CoreN Message: " << dump(body));
            if (handler) {
                handler(CoreN::UnexpectedError, err_type, err_data);
            }
            break;
        }
    }
}

const Service::Address& VirtualService::Remote() const
{
    static const Service::Address addr { virtual_service_name, "", 0};
    return addr;
}

}
