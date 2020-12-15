#include <tuple>
#include <iostream>
#include <type_traits>
#include <vector>
#include <list>

template <typename T>
struct is_vector_or_list : std::false_type {};

template <typename T>
struct is_vector_or_list<std::vector<T>> : std::true_type {};

template <typename T>
struct is_vector_or_list<std::list<T>> : std::true_type {};

template <typename T,
          typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
void print_ip(const T &ip) {
    const auto *ptr = reinterpret_cast<const uint8_t *>(&ip);
    for ( int i = 0; i < sizeof(ip); ++i ) {
        std::cout << static_cast<int>(ptr[i]);  // make it printable
        if ( i < sizeof(ip) - 1 )
            std::cout << ".";
    }
    std::cout << std::endl;
}

template <typename T,
          typename std::enable_if<std::is_same<T, std::string>::value>::type* = nullptr>
void print_ip(const T &ip) {
    std::cout << ip << std::endl;
}

template <typename T,
          typename std::enable_if<is_vector_or_list<T>::value>::type* = nullptr>
void print_ip(const T &ip) {
    for ( auto [i, it] = std::tuple(0, ip.cbegin()); it != ip.cend(); ++i, ++it ) {
        std::cout << *it;
        if ( i != ip.size() - 1 )
            std::cout << ".";
    }
    std::cout << std::endl;
}

int main() {

    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(int(8875824491850138409));
    print_ip(std::string("8.8.8.8"));
    print_ip(std::vector<int>{1,2,3,4});
    print_ip(std::list<int>{10,20,30,40});

    return 0;
}
