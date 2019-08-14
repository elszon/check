#include "Message.h"

#include <cstdlib>
#include <iostream>

namespace check {
Message::~Message() try {
    oss << "\n+=====================+\n";
    if (outputConsumers.empty()) {
        std::cout << msg() << std::endl;
    } else {
        const auto& msgStr = msg();
        for (auto&& output : outputConsumers) {
            output(msgStr);
        }
    }
} catch (...) {
    // any better idea how to manage error handling ?
    std::exit(-1);
}

}  // namespace check
