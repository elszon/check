#pragma once

#include <bitset>
#include <cassert>
#include <unordered_map>

#include "Message.h"

namespace check {

enum class Destination {
    Unknown = 1 << 0,
    Log = 1 << 1,
    Exception = 1 << 2,
    Terminate = 1 << 3,
};

constexpr Destination operator|(Destination lhs, Destination rhs) noexcept {
    return static_cast<Destination>(static_cast<int>(lhs) | static_cast<int>(rhs));
}
constexpr bool operator&(Destination lhs, Destination rhs) noexcept {
    return static_cast<bool>(static_cast<int>(lhs) & static_cast<int>(rhs));
}

class MessageDemultiplexer {
public:
    void handleMessage(const Message& msg) {
        const Destination dest = demux.at(msg.error());
        if (dest & Destination::Log) {
            log(msg);
        }
        if (dest & Destination::Terminate) {
            terminate(msg);
        }
        if (dest & Destination::Exception) {
            throwException(msg);
        }
    }

    template<typename DontBotherIfNotUsed = void>
    static bool setOnlyOne(ErrorType e) noexcept {
        return !(static_cast<int>(e) & (static_cast<int>(e) - 1));
    }

    void setHandle(ErrorType e, Destination d) {
        assert(setOnlyOne<>(e));
        demux[e] = d;
    }

private:
    ///
    /// Consider to have std::function<void(const Message&)> to register some behaviors
    ///
    void log(const Message& msg) const;
    void throwException(const Message& msg) const;
    void terminate(const Message& msg) const;

    std::unordered_map<ErrorType, Destination> demux{
        {ErrorType::Unknown, Destination::Unknown},
        {ErrorType::HW, Destination::Terminate},
        {ErrorType::Performance, Destination::Exception},
        {ErrorType::Other, Destination::Log}};
};

}  // namespace check
