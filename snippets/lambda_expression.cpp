#include <iostream>

template<class T>
auto mmax(T a, T b) {
    return a > b ? a : b;
}

auto max = [](auto a, auto b) -> auto {
    return a > b ? a : b;
};

int main() {
    std::cout << max(1, 2) << " " << max(1.0, 2.0) << " " << max("abc", "abcc") << std::endl;
    return 0;
}