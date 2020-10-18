#include "lib/types.hpp"
#include "lib/utils.hpp"
#include "lib/ips_reverse_sort.hpp"


int main(int argc, char const *argv[]) {
    ips_t ips_pool = ips_read_from_cin();

    ips_reverse_sort_inplace(ips_pool);

    ips_print(ips_pool);
}