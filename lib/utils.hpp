#pragma once

#include "types.hpp"

std::vector<std::string> split(const std::string &, char);
ips_t ips_read_from_cin();
void ips_print(const ips_t&);