#include <iostream>
using namespace std;

int main() {
    std::string s = "1234567890";
    std::string_view sv = s;
    std::cout << sv.substr(5, 3) << std::endl;
    return 0;
}