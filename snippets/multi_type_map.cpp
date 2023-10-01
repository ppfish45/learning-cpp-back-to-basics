#include <map>
#include <set>
#include <string>
#include <iostream>

template<typename V, typename ...Ts>
class multitype_map {
private:
    std::map<std::string, void*> m;

    template<typename A>
    void __init__() {}

    template<typename A, typename B, typename ...Bs>
    void __init__() {
        std::string tn = typeid(B).name();
        m[tn] = new std::map<B, A>();
        __init__<A, Bs...>();
    }

public:
    multitype_map() {
       __init__<V, Ts...>();
    }

    template<typename A>
    void set(A k, V v) {
        std::map<A, V>* mm = (std::map<A, V>*)m[typeid(A).name()];
        (*mm)[k] = v;
    }

    template<typename A>
    V get(A k) {
        std::map<A, V>* mm = (std::map<A, V>*)m[typeid(A).name()];
        return (*mm)[k];
    }
};

int main() {
    multitype_map<int, int, std::string> m;
    m.set<std::string>("123", 111);
    m.set<int>(123, 112221);
    m.set<int>(1232323, 22112221);
    std::cout << m.get<std::string>("123") << std::endl;
    std::cout << m.get<int>(123) << std::endl;
    std::cout << m.get<int>(1232323) << std::endl;
    return 0;
}