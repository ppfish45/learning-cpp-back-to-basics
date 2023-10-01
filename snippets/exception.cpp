#include <iostream>

int main() {
    try {
        throw std::overflow_error("error");
    } catch (const std::overflow_error& ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}