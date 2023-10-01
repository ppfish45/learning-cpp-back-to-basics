#include <cstring>
#include <iostream>

class string {
private:
    void __reserve__(size_t sz) {
        if (sz <= size || sz <= 16) return;
        
        size_t newSize = std::max(size, (size_t)1);
        while (newSize < sz) {
            newSize <<= 1;
        }

        char* newArr = new char[newSize];
        if (arr != nullptr) {
            memcpy(newArr, arr, size);
            delete arr;
        } else {
            memcpy(newArr, sArr, 16);
        }

        arr = newArr;
        size = newSize;
    }

    void __init__(const char* s) {
        len = strlen(s);
        size = 0;
        arr = nullptr;
        if (len < 16) {
            memcpy(sArr, s, len);
            sArr[len] = 0;
        } else {
            __reserve__(len + 1);
            memcpy(arr, s, len);
            arr[len] = 0;
        }
    }

    void __init_from_str__(const string& str) {
        if (str.len < 16) {
            __init__(str.sArr);
        } else {
            __init__(str.arr);
        }
    }

    void __delete__() {
        if (arr != nullptr) {
            delete arr;
        }
        len = size = 0;
    }

public:
    string() : len(0), size(0), arr(nullptr) {
        sArr[0] = 0;
    }

    string(const char* s) {
        __init__(s);
    }

    // copy constructor
    string(const string& str) {
        __init_from_str__(str);
    }

    // move constructor
    string(string&& str) {
        __init_from_str__(str);
        str.__delete__();
    }

    // deconstruct
    ~string() {
        __delete__();
    }

    void operator +=(const string& str) {
        size_t newLen = len + str.len;
        __reserve__(newLen + 1);

        char* dst = newLen < 16 ? sArr : arr;
        const char* src = str.len < 16 ? str.sArr : str.arr;

        memcpy(dst + len, src, str.len);
        dst[newLen] = 0;

        len = newLen;
    }

    void push_back(char c) {
        __reserve__((++len) + 1);
        char* dst = len < 16 ? sArr : arr;
        dst[len - 1] = c;
        dst[len] = 0;
    }

    friend std::ostream& operator << (std::ostream& o, const string& s) {
        if (s.len < 16) {
            o << s.sArr;
        } else {
            o << s.arr;
        }
        return o;
    }

private:
    char sArr[16];
    char* arr;
    size_t len;
    size_t size;
};

int main() {
    string s{"123123123"};
    string p{"12312312312312"};
    s += p;
    for (int i = 0; i < 50; i++) {
        s.push_back('a' + i % 26);
        std::cout << s << std::endl;
    }
    return 0;
}