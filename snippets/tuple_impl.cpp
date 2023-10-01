#include <iostream>
#include <string>

template<typename ...Ts> class tuple;

template<>
class tuple<> {
public:
    tuple<>() = default;
};

template<typename T>
class tuple<T> : tuple<> {
private:
    T val;
public:
    tuple<T>() = default;
    explicit tuple<T>(T _val) : val(_val) {}
    T get() { return val; }
};

template<typename T, typename ...Ts>
class tuple<T, Ts...> : tuple<Ts...> {
    T val;
public:
    tuple<T, Ts...>() = default;
    explicit tuple<T, Ts...>(T _val, Ts ...args) : val(_val) {
        tuple<Ts...>(args...);
    }
    T get() { return val; }
};

template<size_t I, typename ...Ts> struct tuple_type;

template<typename T, typename ...Ts>
struct tuple_type<0, T, Ts...> {
    using value_type = T;
    using tu_type = tuple<T, Ts...>;
};

template<size_t I, typename T, typename ...Ts>
struct tuple_type<I, T, Ts...> {
    using value_type = typename tuple_type<I - 1, Ts...>::value_type;
    using tu_type = typename tuple_type<I - 1, Ts...>::tu_type;
};

template<size_t I, typename ...Ts>
typename tuple_type<I, Ts...>::value_type get(tuple<Ts...> &t) {
    using real_type = typename tuple_type<I, Ts...>::tu_type;
    return ((real_type*)&t)->get();
}

int main() {
    tuple<int, std::string, double> a{1, "123", 3.};
    std::cout << get<0>(a) << std::endl;
    std::cout << get<1>(a) << std::endl;
    std::cout << get<2>(a) << std::endl;
    return 0;
}