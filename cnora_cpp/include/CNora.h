#ifndef COREN_CNORA_H
#define COREN_CNORA_H

#include <string>
#include <vector>
#include <list>

#include <boost/function.hpp>
#include <boost/variant.hpp>
#include <boost/chrono/chrono.hpp>

#include "Interface.h"
#include "ASN1_Service.hpp"

#include <DbResponse.h>
#include <DbRequest.h>

namespace CoreN {

#ifndef COREN_CNORA_CPP
extern char cnora_label[];
#else
char cnora_label[] = "cnora.asn1";
#endif

class CNora
    : public ASN1_Service_Complex_Type(cnora_label, DbResponse, DbRequest)
{
public:
    CNora(const InterfacePtr& I, const Service::Address& remote_,
        const boost::chrono::milliseconds& timeout_);

    // Request Flags
    typedef int Flags;
    enum {
        StopSession = 0x02,
        Commit      = 0x04,
        OneDataset  = 0x20
    };

    // Response Codes
    enum {
        CNE_OK        = 0,
        CNE_MORE      = 1,
        CNE_DB_ERROR  = 4,
        CNE_SYS_ERROR = 5
    };


    typedef boost::variant<nullptr_t, long, double, std::string> Value;
    typedef std::list<Value> Values;
    typedef std::vector<Value> Row;
    typedef std::list<Row> Rows;

    typedef boost::function<void (const Rows& dataset)> DataHandler;
    typedef boost::function<void (const CoreN::Error& error)> FinishHandler;

    void Request(const std::string& sql, const Values& bindings, Flags flags,
        DataHandler d_handler, FinishHandler f_handler);

private:
    void EncodeValues(DbValues* p_values, const Values& values);
    void DecodeDataset(Rows& rows, const DbRows* p_dataset);

    void Helper(const SessionTPtr& sess, const CoreN::Error& error,
        const RecvMessagePtr& body, Session::Flags flags,
        DataHandler d_handler, FinishHandler f_handler);

private:
    Service::Address remote;
    boost::chrono::milliseconds timeout;
};

typedef boost::shared_ptr<CNora> CNoraPtr;

}

#endif // COREN_CNORA_H
