#include "lib.hpp"

int main() {

    std::cout << get_ip(char(-1)) << std::endl;
    std::cout << get_ip(short(0)) << std::endl;
    std::cout << get_ip(int(2130706433)) << std::endl;
    std::cout << get_ip(int(8875824491850138409)) << std::endl;
    std::cout << get_ip(std::string("8.8.8.8")) << std::endl;
    std::cout << get_ip(std::vector<int>{1,2,3,4}) << std::endl;
    std::cout << get_ip(std::list<int>{10,20,30,40}) << std::endl;

    return 0;
}
