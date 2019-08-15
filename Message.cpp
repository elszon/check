#include "Message.h"

#include <cstdlib>
#include <iostream>

namespace check {
Message::~Message() try {
    oss << "\n+=====================+\n";
    if (!handleOutput) {
        std::cout << msg() << std::endl;
    } else {
        handleOutput(msg());
    }
} catch (...) {
    // any better idea how to manage error handling ?
    std::exit(-1);
}

}  // namespace check
