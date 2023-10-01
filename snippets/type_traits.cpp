#include <iostream>
#include <type_traits>

template<class T>
void printNum(T x) {
    static_assert(std::is_arithmetic<T>::value, "not a number");
    std::cout << x << std::endl;
}

int main() {
    printNum(123);
    //printNum("can not compile");
    return 0;
}