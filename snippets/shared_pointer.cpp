#include <atomic>
#include <iostream>

template<class T>
class sharedPtr {
private:
    T* ptr;
    uint* refCount;

    void __cleanup__() {
        if (refCount == nullptr) {
            // be moved away
            return;
        }

        (*refCount)--;
        if (*refCount == 0) {
            delete refCount;
            if (ptr != nullptr) {
                delete ptr;
            }
        }
    }

public:
    sharedPtr(T* _ptr = nullptr) {
        ptr = _ptr;
        refCount = new uint(0);
        if (ptr != nullptr) {
            (*refCount)++;
        }
    }

    // copy constructor
    sharedPtr(const sharedPtr &sPtr) {
        ptr = sPtr.ptr;
        refCount = sPtr.refCount;
        if (ptr != nullptr) {
            (*refCount)++;
        }
    }
 
    // copy assignment
    void operator=(const sharedPtr &sPtr) {
        ptr = sPtr.ptr;
        refCount = sPtr.refCount;
        if (ptr != nullptr) {
            (*refCount)++;
        }
    }

    // move assignement
    void operator=(sharedPtr &&sPtr) {
        __cleanup__();

        ptr = sPtr.ptr;
        refCount = sPtr.refCount;

        sPtr.ptr = nullptr;
        sPtr.refCount = nullptr;
    }
    
    // deconstructor
    ~sharedPtr() {
        __cleanup__();
    }

    // get raw pointer
    T* get_raw_pointer() {
        return ptr;
    }
    
    // p->m = (p.operator->())->m
    T* operator->() {
        return ptr;  
    }

    // *p = (p.operator*())
    T& operator*() {
        return *ptr;
    }

    uint get_count() {
        return *refCount;
    }
};

int main() {
    sharedPtr<int> t(new int(4));
    {
        sharedPtr<int> p(t);
        std::cout << p.get_count() << std::endl;
        (*p)++;
        std::cout << *p << " " << *t << std::endl;
    }
    std::cout << t.get_count() << std::endl;
    sharedPtr<int> tt;
    tt = std::move(t);
    std::cout << (t.get_raw_pointer() == nullptr) << std::endl;
    std::cout << *tt << " " << tt.get_count() << std::endl;
    return 0;
}