#pragma once

#include <iostream> //TODO remove

#include "Message.h"

namespace check {

struct Boolean {
    explicit Boolean(bool c) : condition(c) {}
    bool condition;
    explicit operator bool() { return condition; }
};

template<typename L, typename R>
struct Equal : Boolean {
    explicit Equal(const L& l, const R& r) : Boolean{l == r}, r{r}, l{l} {}
    R r;
    L l;
};

template<typename L, typename R>
struct Less : Boolean {
    explicit Less(const L& l, const R& r) : Boolean{l < r}, r{r}, l{l} {}
    R r;
    L l;
};

}  // namespace check


//TODO remove
auto stdCout = [](const std::string& s) {
    std::cout << "[Output Consumers output]:\n" << s << std::endl;
};

#define CHECK(b)                                                                                   \
    if (check::Boolean c = check::Boolean(b))                                                      \
        ;                                                                                          \
    else                                                                                           \
        check::Message{#b} << '\n'

#define CHECK_EQ(a, b)                                                                             \
    if (check::Equal c = check::Equal(a, b))                                                       \
        ;                                                                                          \
    else                                                                                           \
        check::Message{{stdCout}, #a, " is not equal to ", #b}                                     \
            << "\nvalue of " << #a << " is [" << c.r << "]\nvalue of " << #b << " is [" << c.l     \
            << "]\n"

#define CHECK_LT(a, b)                                                                             \
    if (check::Less c = check::Less(a, b))                                                         \
        ;                                                                                          \
    else                                                                                           \
        check::Message{#a, " is not less than ", #b} << "\nvalue of " << #a << " is [" << c.r      \
                                                     << "]\nvalue of " << #b << " is [" << c.l     \
                                                     << "]\n"
