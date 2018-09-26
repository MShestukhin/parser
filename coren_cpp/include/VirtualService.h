#ifndef VIRTUAL_SERVICE_H
#define VIRTUAL_SERVICE_H

#include "ASN1_Service.hpp"

#include <CoreNProtocol.h>

namespace CoreN {

/*Имя виртуальной службы*/
#ifndef VIRTUAL_SERVICE_CPP
extern char virtual_service_name[];
extern char virtual_service_label[];
#else
char virtual_service_name[] = "CoreN";
char virtual_service_label[] = "CoreN";
#endif

class VirtualService : public ASN1_Service_Type(virtual_service_label, CoreNProtocol)
{
public:
    VirtualService(const InterfacePtr& interface_);
    void DefaultMessageHandler(const SessionTPtr& sess, const Error& error, const RecvMessagePtr& body, Session::Flags flags);

    typedef boost::function<void (const Error& error)> SetSvcNameCallback;
    void SetSvcName(const Service::Name& svc_name, int svc_priority, SetSvcNameCallback handler);

    void Info(Info::Callback handler, Info::Type type = Info::Route);

private:
    void SetSvcNameResponse(const SessionTPtr& sess, const Error& error, const RecvMessagePtr& body, Session::Flags flags, SetSvcNameCallback handler);
    void InfoResponse(const SessionTPtr& sess, const Error& error, const RecvMessagePtr& body, Session::Flags flags, Info::Callback handler);

    const Service::Address& Remote() const;
};

}

#endif /* VIRTUAL_SERVICE_H */
