#include <iostream>
#include <type_traits>
#include <vector>

template <class T, typename Fake = typename std::enable_if<std::is_integral<T>::value>::type>
void print_ip(T ip) {
    auto *ptr = reinterpret_cast<uint8_t *>(&ip);
    for ( int i = 0; i < sizeof(ip); ++i ) {
        std::cout << static_cast<int>(ptr[i]);  // make it printable
        if ( i < sizeof(ip) - 1 )
            std::cout << ".";
    }
    std::cout << std::endl;
}

void print_ip(const std::string &ip) {
    std::cout << ip << std::endl;
}

//template <class T,
//        typename Fake = typename std::enable_if<std::is_same<T, std::vector>>
//void print_ip(const T &ip) {
//    for ( auto x : ip ) {
//        std::cout << x << ".";
//    }
//    std::cout << std::endl;
//}

int main() {

    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(int(8875824491850138409));
    print_ip("8.8.8.8");
//    print_ip(std::vector<int>{1,2,3,4});

    return 0;
}
