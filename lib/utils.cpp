#include "utils.hpp"
#include <iostream>

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

ips_t ips_read_from_cin() {
    ips_t ip_pool;
    for (std::string line; std::getline(std::cin, line);) {
        std::vector<std::string> v = split(line, '\t');

        ip_t ip;
        {
            int i = 0;
            for (const std::string &s : split(v.at(0), '.')) {
                if ( i > 4 )
                    break;
                ip[i] = std::stoi(s);
                i++;
            }
            if ( i != 4 )
                return {};
        }
        ip_pool.push_back(ip);
    }
    return ip_pool;
}

void ips_print(const ips_t& ips_pool) {
    for( const ip_t &ip : ips_pool ) {
        for(auto iter = ip.cbegin(); iter != ip.cend(); ++iter) {
            if (iter != ip.cbegin()) {
                std::cout << ".";
            }
            std::cout << std::to_string(*iter);
        }
        std::cout << std::endl;
    }
}