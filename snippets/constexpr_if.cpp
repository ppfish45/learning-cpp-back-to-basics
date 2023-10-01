#include <iostream>

template<typename T>
T func(T a, T b) {
    if constexpr(std::is_arithmetic<T>::value) {
        if (a > b) return a;
        return b;
    } else if constexpr(std::is_same<T, std::string>::value) {
        return a + b;
    } else if constexpr(std::is_same<T, const char*>::value) {
        return b;
    }
    return a;
}

int main() {
    std::cout << func(1, 3) << std::endl;
    std::cout << func(1.3, 3.5) << std::endl;
    std::cout << func(std::string{"aaa"}, std::string{"bbb"}) << std::endl;
    std::cout << func("aaa", "bbb") << std::endl;
    std::cout << func('a', 'b') << std::endl;
    return 0;
}