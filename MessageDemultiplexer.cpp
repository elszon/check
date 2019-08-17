#include "MessageDemultiplexer.hpp"

#include <iostream>

namespace check {
void MessageDemultiplexer::log(const Message& msg) const {
    std::cout << msg.msg() << std::endl;
}

void MessageDemultiplexer::throwException(const Message& msg) const {
    log(msg);
    throw std::runtime_error{msg.msg()};
}

void MessageDemultiplexer::terminate(const Message& msg) const {
    log(msg);
    std::exit(static_cast<int>(msg.error()));
}

}  // namespace check
