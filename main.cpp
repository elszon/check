#include <iostream>

#include "check.hpp"

int foo(){
    return 1;
}

int main()
{
    bool t{true};
    CHECK(t) << " need true ";
    CHECK(false) << "is false but need true ";
    CHECK_EQ(1,2) << "not equal values _1 and _2";
    CHECK_LT(4,2) << "not less than values _4 and _2";
    int a{10};
    int b{11};
    CHECK_EQ(a,b) << "not equal members";
    CHECK_EQ(foo(),b) << "not equal members";


    std::cout << "Hello World!" << std::endl;
    return 0;
}
