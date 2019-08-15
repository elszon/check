#include "check.hpp"

#include <iostream>

namespace check {

std::function<void(const Message& msg)> MsgHandler::msgHandler;

void MsgHandler::reset(MsgHandler::Handler h) {
    // mutex an scope_lock might be use here
    msgHandler = h;
}

void MsgHandler::handle(const Message& msg) {
    // mutex an scope_lock might be use here
    if (msgHandler) {
        msgHandler(msg);
    } else {
        std::cout << " No message handler registered => \n" << msg.msg() << std::endl;
    }
}

Output& Output::operator=(const Message& msg) {
    MsgHandler::handle(msg);
    return *this;
}

}  // namespace check
