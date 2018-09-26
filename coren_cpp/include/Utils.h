#ifndef UTILS_H
#define UTILS_H

#include <ostream>

#include "Types.h"

#ifndef _MsgAddr_H_
struct MsgAddr;
#endif

namespace CoreN {
    namespace Utils {
        Session::Name GenerateId(const Service::Type& label);
        Service::Address Address(const MsgAddr& addr);
        std::string RoleToString(Service::Role role);
    }
}

std::ostream& operator <<(std::ostream& oss, const CoreN::Error& e);
std::ostream& operator <<(std::ostream& oss, const CoreN::Service::Address& addr);

#endif /* UTILS_H */
