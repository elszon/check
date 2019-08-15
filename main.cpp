#include <iostream>

#include "check.hpp"

int foo(){
    return 1;
}

int main()
{
    bool t{true};
    CHECK(check::ErrorType::Unknown, t) << " need true ";
    CHECK(check::ErrorType::Unknown, false) << "is false but need true ";
    CHECK_EQ(check::ErrorType::Unknown, 1,2) << "not equal values _1 and _2";
    CHECK_LT(check::ErrorType::Unknown, 4,2) << "not less than values _4 and _2";
    int a{10};
    int b{11};
    CHECK_EQ(check::ErrorType::Unknown, a,b) << "not equal members";
    CHECK_EQ(check::ErrorType::Unknown, foo(),b) << "not equal members";


    std::cout << "Hello World!" << std::endl;
    return 0;
}
