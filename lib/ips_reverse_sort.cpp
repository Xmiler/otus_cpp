#include "ips_reverse_sort.hpp"
#include <vector>
#include <string>
#include <algorithm>


void ips_reverse_sort_inplace(ips_t &ip_pool) {
    std::sort(ip_pool.begin(), ip_pool.end(),
              [](const ip_t &ip1, const ip_t &ip2) {
                  return std::lexicographical_compare(
                          ip1.cbegin(), ip1.cend(),
                          ip2.cbegin(), ip2.cend(),
                          [](const std::string &byte1, const std::string &byte2) {
                              return std::stoi(byte1) > std::stoi(byte2);
                          }
                  );
              }
    );
}
