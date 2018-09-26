CNora Service Client
====================

This library is implementation of CNora Service client,
and may be used for a simple accsess to database from application.

Usage
-----

```cpp

#include "Incterface.h" // CoreN
#include "CNora.h"

// Create and Registre Service
CoreN::CNoraPtr getCNora(const CoreN::InterfacePtr& I, const nlohmann::json& config)
{
    const CoreN::Service::Address remote {
        config["svc_name"], "", 0
    };
    CoreN::CNoraPtr svc = boost::make_shared<CoreN::CNora>(I, remote);
    I->AddService(CoreN::cnora_label, boost::dynamic_pointer_cast<CoreN::Service::Base>(svc));
    return svc;
}

// ...

// Do request
const CoreN::CNoraPtr& cnora = getCNora(I, "{ \"svc_name\": \"GMSU-Cnora\" }");
cnora->Request(
    "SELECT 2+2 res;", // SQL
    CoreN::CNora::Values(), // Binded params (now empty)
    CoreN::CNora::Commit | CoreN::CNora::StopSession, // Some flags for request
    [](const CoreN::CNora::Rows& dataset) {
        for (auto row : dataset) {
            for (auto column : row) {
                // Somethig like this
                std::cout << boost::apply_visitor(MyTypePrintVisitor(), column) << "\t";
                // See: http://www.boost.org/doc/libs/1_64_0/doc/html/variant/tutorial.html
            }
            std::cout << std::endl;
        }
    }, // Method on data recv
    [](const CoreN::Error& error){
        std::cout << "Request status: " << error << std::endl;
    } // Method on request finish
);


```

