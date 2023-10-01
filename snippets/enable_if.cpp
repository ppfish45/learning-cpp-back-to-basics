#include <iostream>
#include <type_traits>

template<class T>
typename std::enable_if<sizeof(T) <= 4, size_t>::type
get_size_of(T x)
{
	return sizeof(x);	
}

int main() {
    std::cout << get_size_of((long long)4) << std::endl;
    return 0;
}