#include <iostream>

template<typename T, size_t D>
class point {
private:
    T* arr;
public:
    point() {
        arr = new T[D];
    }

    point(std::initializer_list<T> _arr) {
        arr = new T[D];
        auto cur = _arr.begin();
        for (int i = 0; i < D && cur != _arr.end(); i++, cur++) {
            arr[i] = *cur;
        }
    }

    // move
    explicit point(point<T, D> && p) {
        arr = p.arr;
        p.arr = nullptr;
    }

    // copy
    explicit point(point<T, D> & p) {
        arr = new T[D];
        memcpy(arr, p.arr, sizeof(T) * D);
    }

    T& operator[](size_t id) {
        return arr[id];
    }

    ~point() {
        delete[] arr;
    }
};

int main() {
    point<int, 5> p({1, 2, 3, 4, 5});
    std::cout << p[0] << std::endl;
    std::cout << p[3] << std::endl;
    std::cout << p[2] << std::endl;
    return 0;
}