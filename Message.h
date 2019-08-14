#pragma once

#include <functional>
#include <sstream>
#include <string>
#include <vector>

namespace check {
class Message {
public:
    using OutputFun = std::function<void(const std::string& msg)>;
    using OutputConsumers = std::vector<OutputFun>;

    template<typename... Args>
    Message(const Args&... args) {
        oss << "Is not valid: [ ";
        const auto fold = {(oss << args, 0)...};
        (void)fold;
        oss << " ] ";
    }

    template<typename... Args>
    Message(OutputConsumers outputConsumers, const Args&... args)
        : outputConsumers{outputConsumers} {
        oss << "Is not valid: [ ";
        const auto fold = {(oss << args, 0)...};
        (void)fold;
        oss << " ] ";
    }

    ~Message();

    template<typename T>
    Message& operator<<(const T& t) {
        oss << t;
        return *this;
    }

    std::string msg() const { return oss.str(); }

private:
    std::ostringstream oss;
    OutputConsumers outputConsumers;
};

}  // namespace check
