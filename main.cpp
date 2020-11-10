#include <iostream>
#include <map>

template <typename T>
class ArenaAllocator {
public:
    using value_type = T;

    ArenaAllocator() = default;

    template <typename U>
    explicit ArenaAllocator<T>(const ArenaAllocator<U> &) {
    }

    T* allocate(std::size_t n) {

        std::cout << __PRETTY_FUNCTION__ << std::endl;

        auto p = std::malloc(n * sizeof(T));
        if (p == nullptr)
            throw std::bad_alloc();
        return static_cast<T *>(p);
    }

    void deallocate(T* p, std::size_t) {

        std::cout << __PRETTY_FUNCTION__ << std::endl;

        std::free(static_cast<void *>(p));
    }
};

int main() {

    std::map<int, int, std::less<>, ArenaAllocator<int>> m;

    m[0] = 1;
    for ( int i = 1; i < 10; ++i )
        m[i] = m[i-1] * i;

    return 0;
}
