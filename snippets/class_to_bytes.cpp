#include <cstdlib>
#include <iostream>

class test {
private:
    int n;
public:
    test(int _n = 0) : n(_n) {}
    int getValue() { return n; }
};

int main() {
    test t{1000};
    uint8_t* arr = new uint8_t[sizeof(t)];
    memcpy(arr, &t, sizeof(t));    
    std::cout << ((test*)arr)->getValue() << std::endl;
}