#include <iostream>

template<class T>
class vector {
private:
    int size;
    int n;
    T* arr;
    inline void __resizeIfNecessary__() {
        if (n >= size) {
            size <<= 1;
            T* newArr = new T[size];
            for (int i = 0; i < n; i++) {
                newArr[i] = arr[i];
            }
            delete arr;
            arr = newArr;
        }
    }
public:
    vector(): size(1), n(0) {
        arr = new T[1];
    }

    template<typename ...Args>
    void emplace(Args&& ...args) {
        __resizeIfNecessary__();
        arr[n++] = T{std::forward<Args>(args)...};
    }

    T operator[](int id) {
        return arr[id];
    }
};

class testClass {
private:
    int a;
    int b;
    std::string s;
public:
    testClass(): a(0), b(0) {}
    testClass(int a_, int& b_): a(a_), b(b_) {}
    testClass(int a_, int&& b_): a(a_), b(b_) { std::cout << "rvalue init" << std::endl; }
    testClass(int a_, int b_, std::string s_): a(a_), b(b_), s(s_) {}
    void print() {
        std::cout << a << " " << b << " " << s << std::endl;
    }
};

int main() {
    vector<testClass> vec;
    int x = 5;
    vec.emplace(1, 2);
    vec.emplace(3, x);
    vec.emplace(4, 5, "ss");
    vec[0].print();
    vec[1].print();
    vec[2].print();
}
