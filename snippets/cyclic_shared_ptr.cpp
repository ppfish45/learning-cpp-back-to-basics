#include <iostream>

struct A;
struct B;

struct A {
    std::shared_ptr<B> to;
};

struct B {
    std::weak_ptr<A> to;
};

int main() {
    A* a = new A();
    B* b = new B();
    auto pA = std::shared_ptr<A>(a);
    auto pB = std::shared_ptr<B>(b);
    pA->to = pB;
    pB->to = pA;
    std::cout << pA.use_count() << std::endl;
    std::cout << pB.use_count() << std::endl;
    return 0;
}