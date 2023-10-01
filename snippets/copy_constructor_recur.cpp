#include <iostream>

class Test {
private:
    int value_;
public:
    Test(const int &val_) : value_(val_) {}
    Test(const Test &t) {
        std::cout << "copy instructor" << std::endl;
        value_ = t.value_;
    }
};

int main() {
    Test t1{123};
    Test t2{t1};
    return 0;
}