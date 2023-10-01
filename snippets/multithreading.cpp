#include <thread>
#include <string>
#include <iostream>

class callable {
public:
    void operator()(std::string arg) {
        std::cout << "from function object -> " << arg << std::endl;
    }
};

void callableFunc(std::string arg) {
    std::cout << "from function pointer -> " << arg << std::endl;
}

int main()
{
    callable c;
    // use function object
    std::thread t1(c, "test");
    // use function pointer
    std::thread t2(callableFunc, "test");
    // use lambda expression
    std::thread t3([](std::string arg){
        std::cout << "from lambda expression -> " << arg << std::endl;
    }, "test");

    t1.join();
    t2.join();
    t3.join();
}