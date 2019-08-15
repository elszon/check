#pragma once

#include <cassert>
#include <functional>

#include "Message.h"

namespace check {

struct Boolean {
    explicit constexpr Boolean(bool c) : condition(c) {}
    explicit constexpr operator bool() const { return condition; }
    const bool condition;
};

template<typename T, template<typename C> class Cmp>
struct BinaryCheck : Boolean {
    explicit BinaryCheck(const T& l, const T& r) : Boolean{Cmp<T>{}(l, r)}, l{l}, r{r} {}
    const T l;
    const T r;
};

template<typename T>
using Equal = BinaryCheck<T, std::equal_to>;

template<typename T>
using NotEqual = BinaryCheck<T, std::not_equal_to>;

template<typename T>
using Less = BinaryCheck<T, std::less>;

template<typename T>
using Greater = BinaryCheck<T, std::greater>;

template<typename T>
using LessEqual = BinaryCheck<T, std::less_equal>;

template<typename T>
using GreaterEqual = BinaryCheck<T, std::greater_equal>;


class Output {
public:
    Output& operator=(const Message& msg);
};



///
/// \brief The MsgHandler class allow to register handler for Message create when check is invalid
///
class MsgHandler {
public:
    using Handler = std::function<void(const Message& msg)>;
    static void reset(Handler h = {});
    static void handle(const Message& msg);
private:
    static std::function<void(const Message& msg)> msgHandler;
};



}  // namespace check

#define CHECK(errorType, b)                                                                        \
    if (check::Boolean c = check::Boolean(b))                                                      \
        ;                                                                                          \
    else                                                                                           \
        check::Output{} = check::Message{errorType, #b} << '\n'

#define BINARY_CHECK(errorType, a, b, CMP, CMP_MSG)                                                \
    if (check::CMP<decltype(a)> c = check::CMP<decltype(a)>(a, b))                                 \
        ;                                                                                          \
    else                                                                                           \
        check::Output{} = check::Message{errorType, #a, CMP_MSG, #b}                               \
                          << "\nvalue of " << #a << " is [" << c.r << "]\nvalue of " << #b         \
                          << " is [" << c.l << "]\n"

#define CHECK_EQ(errorType, a, b) BINARY_CHECK(errorType, a, b, Equal, " is equal to ")

#define CHECK_NE(errorType, a, b) BINARY_CHECK(errorType, a, b, NotEqual, " is not equal to ")

#define CHECK_LT(errorType, a, b) BINARY_CHECK(errorType, a, b, Less, " is less than ")

#define CHECK_GT(errorType, a, b) BINARY_CHECK(errorType, a, b, Greater, " is greater than ")

#define CHECK_LE(errorType, a, b) BINARY_CHECK(errorType, a, b, LessEqual, " is less or equal to ")

#define CHECK_GE(errorType, a, b)                                                                  \
    BINARY_CHECK(errorType, a, b, GreaterEqual, " is greater or equal to ")
