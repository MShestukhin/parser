#include "MsgAddr.h"
#include "Utils.h"

#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include "asn_utils.h"

static std::string random_string(size_t length = 32)
{
    static const std::string chars(
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "1234567890"
        //"!@#$%^&*()"
        //"`~-_=+[{]{\\|;:'\",<.>/? "
    );
    static boost::random::random_device rng;
    static boost::random::uniform_int_distribution<> index_dist(0, chars.size() - 1);
    std::string result;
    for(size_t i = 0; i < length; ++i) {
        result += chars[index_dist(rng)];
    }
    return result;
}

namespace CoreN {

namespace Utils {

Session::Name GenerateId(const Service::Type& label)
{
    return (label.empty() ? "" : label + "_") + random_string();
}

Service::Address Address(const MsgAddr& addr)
{
    Service::Address res;
    res.service    = asn1::cast::asnUTF8StringToString(addr.svcname);
    res.node       = asn1::cast::asnUTF8StringToString(addr.hostname);
    if (addr.svcconn) {
        res.connection = asn1::cast::asnINTEGERToLong(addr.svcconn);
    }
    return res;
}

std::string RoleToString(Service::Role role)
{
    switch (role) {
        case Service::Master:
            return "Master";
            break;
        case Service::Slave:
            return "Slave";
            break;
        case Service::Detect:
            return "Detect";
            break;
        default:
            return "Unknown";
            break;
    }
}

}

}

std::ostream& operator <<(std::ostream& oss, const CoreN::Error& e)
{
    return oss << "(" << e.code << ", \"" << e.message << "\")";
}

std::ostream& operator <<(std::ostream& oss, const CoreN::Service::Address& addr)
{
    return oss << "/" << addr.service << "/" << addr.node << ":" << addr.connection;
}
