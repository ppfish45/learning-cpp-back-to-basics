#include <iostream>

void test(int x) {
    std::cout << x << std::endl;
}

template<class T>
void test(T x) = delete;

int main() {
    test(1000);
    test(1000.1);
    return 0;
}