#pragma once

#include "types.hpp"

std::vector<std::string> split(const std::string &, char);
std::pair<ips_t, bool> ips_read_from_cin();
void ips_print(const ips_t&);