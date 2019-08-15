#include "Message.h"

#include <cstdlib>
#include <iostream>

namespace check {

std::ostream& operator<<(std::ostream& os, ErrorType e) {
    switch (e) {
        default:
        case ErrorType::Unknown: return os << "Unknown";
        case ErrorType::HW: return os << "HW";
        case ErrorType::Performance: return os << "Performance";
        case ErrorType::Other: return os << "Other";
    }
}


}  // namespace check
