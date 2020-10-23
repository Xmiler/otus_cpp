#include "filter.hpp"
#include <algorithm>
#include <functional>

ips_t _filter_impl(const ips_t &ips, const std::function<bool(ip_t)> &predicate) {
    ips_t out;
    std::copy_if(ips.cbegin(), ips.cend(), std::back_inserter(out), predicate);
    return out;
}

// TODO: rewrite it using variadic (?)
ips_t filter(const ips_t &ips, const byte_t &byte0) {
    auto predicate = [&byte0](const ip_t &ip){ return ip[0] == byte0; };
    return _filter_impl(ips, predicate);
}

ips_t filter(const ips_t &ips, const byte_t &byte0, const byte_t &byte1) {
    auto predicate = [&byte0, &byte1](const ip_t &ip){ return ip[0] == byte0 && ip[1] == byte1; };
    return _filter_impl(ips, predicate);
}
// -------------------

ips_t filter_any(const ips_t &ips, const byte_t &byte) {
    auto predicate_byte = [&byte](const byte_t &byte_){ return byte_ == byte; };
    auto predicate = [&predicate_byte](const ip_t &ip) { return std::any_of(ip.cbegin(), ip.cend(), predicate_byte); };
    return _filter_impl(ips, predicate);
}