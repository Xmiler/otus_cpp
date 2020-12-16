#include "lib/types.hpp"
#include "lib/utils.hpp"
#include "lib/reverse_sort.hpp"
#include "lib/filter.hpp"


int main(int argc, char const *argv[]) {
    auto [ips_pool, status] = ips_read_from_cin();
    if ( ! status )
        return 1;

    ips_pool = reverse_sort(ips_pool);

    ips_print(ips_pool);
    ips_print(filter(ips_pool, 1));
    ips_print(filter(ips_pool, 46, 70));
    ips_print(filter_any(ips_pool, 46));

    return 0;
}