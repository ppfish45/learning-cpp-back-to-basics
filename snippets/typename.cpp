#include <iostream>
#include <string>

template<typename T>
void func() {
    T::iterator it;
}

int main() {
    typename std::string s = "123";
    return 0;
}