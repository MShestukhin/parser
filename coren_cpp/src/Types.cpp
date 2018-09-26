/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Types.cpp
 * Author: yurik
 *
 * Created on 21 июля 2017 г., 12:29
 */
#define TYPES_CPP 1
#include "Types.h"

#include <tuple>

namespace CoreN {

    namespace Session {

        const Name EmptyId { "NONE" };

    }

    namespace Service {

        bool operator==(const Address& left, const Address& right) {
            return std::tie(left.service, left.node, left.connection) ==
                   std::tie(right.service, right.node, right.connection);
        }

    }

    const Error ValidationError = { Error::Validation, "Structure Validation error" };
    const Error UnexpectedError = { Error::Unexpected, "Enxpected Message error" };
    const Error TransportError = { Error::Transport, "Transport error" };
    const Error EncodeError = { Error::Encode, "Encode/Decode error" };
    const Error NoError = { Error::None, "OK" };

    Error::operator bool() const
    {
        return (code != Error::None);
    }

}
