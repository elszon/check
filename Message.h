#pragma once

#include <functional>
#include <sstream>
#include <string>
#include <vector>

namespace check {

enum class ErrorType {
    Unknown = 1 << 0,
    HW = 1 << 1,
    Performance = 1 << 2,
    Other = 1 << 3,
};

class Message final {
public:
    using HandleOutputFun = std::function<void(std::string msg)>;

    template<typename... Args>
    Message(ErrorType errorType, const Args&... args) : errorType{errorType} {
        oss << "Is not valid: [ ";
        const auto fold = {(oss << args, 0)...};
        (void)fold;
        oss << " ] ";
    }

    template<typename... Args>
    Message(ErrorType errorType, HandleOutputFun handleOutput, const Args&... args)
        : errorType{errorType}, handleOutput{handleOutput} {
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
    const ErrorType errorType;
    std::ostringstream oss;
    HandleOutputFun handleOutput;
};

}  // namespace check
