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
          typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, bool>::value>::type* = nullptr>
std::string get_ip(const T &ip) {
    std::string out;
    const auto *ptr = reinterpret_cast<const uint8_t *>(&ip);
    for ( int i = 0; i < sizeof(ip); ++i ) {
        out += std::to_string(ptr[i]);
        if ( i < sizeof(ip) - 1 )
            out += ".";
    }
    return out;
}

template <typename T,
          typename std::enable_if<std::is_same<T, std::string>::value>::type* = nullptr>
std::string get_ip(const T &ip) {
    return ip;
}

template <typename T,
          typename std::enable_if<is_vector_or_list<T>::value>::type* = nullptr>
std::string get_ip(const T &ip) {
    std::string out;
    for ( auto [i, it] = std::tuple(0, ip.cbegin()); it != ip.cend(); ++i, ++it ) {
        out += std::to_string(*it);
        if ( i != ip.size() - 1 )
            out += ".";
    }
    return out;
}
