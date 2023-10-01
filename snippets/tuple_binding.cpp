#include <tuple>
#include <iostream>

int main() {
    auto [a, b, c] = std::tuple("a", 2, false);
    std::cout << a << " " << b << " " << c << std::endl;
    return 0;
}