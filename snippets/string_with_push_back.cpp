#include <iostream>

class string {
private:
    char* s;
    size_t len;
    size_t size;

    void __freeup__() {
        if (s != nullptr) {
            delete[] s;
        }
        len = size = 0;
    }

public:
    string() : s(nullptr), len(0), size(0) {}
    string(const char *str) {
        len = strlen(str);
        size = len + 1;
        s = new char[size];
        memcpy(s, str, len);
        s[len] = 0;
    }

    // copy
    string(const string& str) {
        len = str.len;
        size = str.size;
        s = new char[size];
        memcpy(s, str.s, size);
    }

    // move
    string(string && str) {
        len = str.len;
        size = str.size;
        s = str.s;
        str.s = nullptr;
        str.__freeup__();
    }

    // deconstructor
    ~string() {
        __freeup__();
    }

    // push_back
    void push_back(char c) {
        if (len + 1 >= size) {
            int newSize = std::max(size << 1, (size_t) 2);
            char* newPtr = new char[newSize];

            memcpy(newPtr, s, size);
            delete s;
            s = newPtr;
            size = newSize;
        }
        s[len++] = c;
        s[len] = 0;
    }
    
    // operator << overload
    friend std::ostream& operator<<(std::ostream& out, const string &str) {
        out << str.s;
        return out;
    }
};

int main() {
    string s;
    s.push_back('1');
    s.push_back('2');
    s.push_back('3');
    s.push_back('4');
    s.push_back('5');
    std::cout << s << std::endl;
    string b(s);
    std::cout << b << std::endl << s << std::endl;
    string c(std::move(s));
    std::cout << c << std::endl << b << std::endl;
    
}