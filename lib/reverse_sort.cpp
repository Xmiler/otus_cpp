#include "reverse_sort.hpp"
#include <vector>
#include <string>
#include <algorithm>


ips_t reverse_sort(ips_t &ip_pool) {
    ips_t out(ip_pool);
    std::sort(out.begin(), out.end(),
              [](const ip_t &ip1, const ip_t &ip2) {
                  return std::lexicographical_compare(
                          ip1.cbegin(), ip1.cend(),
                          ip2.cbegin(), ip2.cend(),
                          std::greater<>()
                  );
              }
    );
    return out;
}
