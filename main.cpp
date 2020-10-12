#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main(int argc, char const *argv[]) {
    std::vector <std::vector<std::string>> ip_pool;

    for (std::string line; std::getline(std::cin, line);) {
        std::vector <std::string> v = split(line, '\t');
        ip_pool.push_back(split(v.at(0), '.'));
    }

    // TODO reverse lexicographically sort
    std::sort(ip_pool.begin(), ip_pool.end(),
              [](const auto &ip1, const auto &ip2){
        return std::lexicographical_compare(
                ip1.cbegin(), ip1.cend(),
                ip2.cbegin(), ip2.cend(),
                [](const auto &byte1, const auto &byte2){ return std::stoi(byte1) > std::stoi(byte2);});
    });

    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
        for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
            if (ip_part != ip->cbegin()) {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}
