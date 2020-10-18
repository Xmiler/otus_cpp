#include "filter.hpp"
#include <algorithm>
#include <functional>

ips_t _filter(const ips_t &ips, std::function<bool(ip_t)> predicate) {
    ips_t out;
    std::copy_if(ips.cbegin(), ips.cend(), std::back_inserter(out), predicate);
    return out;
}

// TODO: rewrite it using variadic (?)
ips_t filter(const ips_t &ips, const ip_part_t &ip_part0) {
    auto predicate = [&ip_part0](const ip_t &ip){ return ip[0] == ip_part0; };
    return _filter(ips, predicate);
}

ips_t filter(const ips_t &ips, const ip_part_t &ip_part0, const ip_part_t &ip_part1) {
    auto predicate = [&ip_part0, &ip_part1](const ip_t &ip){ return ip[0] == ip_part0 && ip[1] == ip_part1; };
    return _filter(ips, predicate);
}
// -------------------

ips_t filter_any(const ips_t &ips, const ip_part_t &ip_part) {
    auto predicate_ip_part = [&ip_part](const auto &ip_part_){ return ip_part_ == ip_part; };
    auto predicate = [&predicate_ip_part](const ip_t &ip) { return std::any_of(ip.cbegin(), ip.cend(), predicate_ip_part); };
    return _filter(ips, predicate);
}