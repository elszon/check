#pragma once

#include <iostream>  //TODO remove

#include "Message.h"

namespace check {

struct Boolean {
    explicit constexpr Boolean(bool c, ErrorType errorType = ErrorType::Unknown)
        : condition(c), errorType{errorType} {}
    explicit constexpr operator bool() const { return condition; }
    const bool condition;
    const ErrorType errorType;
};

template<typename T, template<typename C> class Cmp>
struct BinaryCheck : Boolean {
    BinaryCheck(const T& l, const T& r, ErrorType errorType = ErrorType::Unknown)
        : Boolean{Cmp<T>{}(l, r), errorType}, l{l}, r{r} {}
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

}  // namespace check

// TODO remove
auto stdCout = [](std::string s) { std::cout << "[Output Consumers output]:\n" << s << std::endl; };

#define CHECK(errorType, b)                                                                        \
    if (check::Boolean c = check::Boolean(b))                                                      \
        ;                                                                                          \
    else                                                                                           \
        check::Message{errorType, #b} << '\n'

#define CHECK_EQ(errorType, a, b)                                                                  \
    if (check::Equal<decltype(a)> c = check::Equal<decltype(a)>(a, b))                             \
        ;                                                                                          \
    else                                                                                           \
        check::Message{errorType, stdCout, #a, " is not equal to ", #b}                            \
            << "\nvalue of " << #a << " is [" << c.r << "]\nvalue of " << #b << " is [" << c.l     \
            << "]\n"

#define CHECK_LT(errorType, a, b)                                                                  \
    if (check::Less<decltype(a)> c = check::Less<decltype(a)>(a, b))                               \
        ;                                                                                          \
    else                                                                                           \
        check::Message{errorType, #a, " is not less than ", #b}                                    \
            << "\nvalue of " << #a << " is [" << c.r << "]\nvalue of " << #b << " is [" << c.l     \
            << "]\n"
