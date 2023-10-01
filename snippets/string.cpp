#include <cstring>
#include <cstdlib>
#include <iostream>

class string {
private:
    char* s;

    void __init__(const char* str) {
        int len = strlen(str);
        s = new char[len + 1];
        memcpy(s, str, len);
        s[len] = 0;
    }

    void __free__() {
        if (s != nullptr) {
            delete[] s;
            s = nullptr;
        }
    }
public:
    string(): s(nullptr) {}

    // construct
    string(const char* str) {
        __init__(str);
    }

    // move
    string(string&& str) {
        std::cout << "move construct" << std::endl;
        __init__(str.s);
        str.__free__();
    }

    // copy
    string(const string& str) {
        std::cout << "copy construct" << std::endl;
        __init__(str.s);
    }

    // deconstructor
    ~string() {
        __free__();
    }

    // <<
    friend std::ostream& operator<<(std::ostream& out, const string& str) {
        if (str.s != nullptr) {
            out << str.s;
        }
        return out;
    }
};

int main() {
    string s1("123");
    string s2(s1);
    string s3(s1);
    string s4(std::move(s3));
    std::cout << s1 << " " << s2 << " " << s3 << " " << s4 << std::endl;
    return 0;
}