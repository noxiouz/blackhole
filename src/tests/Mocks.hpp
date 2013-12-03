#pragma once

#include "Global.hpp"

//logger &log;

//log.debug("message: %s", "str",
//          keyword::verbosity=5);

////pattern="[%(timestamp)s] [%(level)s]: %(message)s%(...other)s"
////[012391232139] [debug] bla: 12313, name: "foo", ...


//LOG(log, debug, "le message: %s", "just some message")(
//    tag::groups(100500),
//    tag::http::code(404),
//    { "groups", 100500 }
//);


///* verbosity: info
// * sink: file
// *   path: [/]
// *   format: string
// *     pattern: [%(...)s] ...
// *
// * sink: tcp/udp
// *   address: 0.0.0.0
// *   port: 5000
// *   format: msgpack/json
// *
// * sink: syslog
// *   identity: blah
// *   format: string
// *     pattern: [%(...)s] ...
// */

//log.debug("%s", "arg1", {
//              "key1": 123
//          })

namespace mock {

class backend_t {
public:
    backend_t(const std::string&) {
        ON_CALL(*this, opened()).
                WillByDefault(Return(true));
    }

    MOCK_CONST_METHOD0(opened, bool());
    MOCK_CONST_METHOD0(path, std::string());

    MOCK_METHOD0(open, bool());
    MOCK_METHOD1(write, void(const std::string&));
};

} // namespace mock