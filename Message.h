#pragma once

#include <sstream>
#include <string>

namespace check {

enum class ErrorType {
    Unknown = 1 << 0,
    HW = 1 << 1,
    Performance = 1 << 2,
    Other = 1 << 3,
};

std::ostream& operator<<(std::ostream& os, ErrorType e);

class Message final {
public:
    template<typename... Args>
    Message(ErrorType errorType, const Args&... args) : errorType{errorType} {
        oss << "Is not true: [ ";
        const auto fold = {(oss << args, 0)...};
        (void)fold;
        oss << " ] ";
    }

    template<typename T>
    Message& operator<<(const T& t) {
        oss << t;
        return *this;
    }

    std::string msg() const { return oss.str(); }
    ErrorType error() const { return errorType; }

private:
    const ErrorType errorType;
    std::ostringstream oss;
};

}  // namespace check
