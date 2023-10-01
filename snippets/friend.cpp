#include <iostream>

class A;
class B;

class A 
{
private:
    int val;
public:
    A(int _val = 0): val(_val) {}
    friend int add(A a, B b);
};

class B
{
private:
    int val;
public:
    B(int _val = 0): val(_val) {}
    friend int add(A a, B b);
};

int add(A a, B b) {
    return a.val + b.val;
}

int main() {
    std::cout << add(A(1), B(2)) << std::endl;
    return 0;
}