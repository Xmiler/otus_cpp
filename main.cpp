#include <map>
#include "lib/arena_allocator.hpp"
#include "lib/forward_list.hpp"
#include "lib/utils.hpp"


int main() {

    std::map<int, int, std::less<>> m1;
    fill_map(m1);

    std::map<int, int, std::less<>, otus::ArenaAllocator<std::pair<const int, int>, 10>> m2;
    fill_map(m2);
    print_map(m2);

    otus::list<int> l1;
    fill_list(l1);

    otus::list<int, otus::ArenaAllocator<int, 10>> l2;
    fill_list(l2);
    print_list(l2);

    return 0;
}
