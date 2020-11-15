#include <iostream>
#include <map>

template <typename T, size_t N>
class ArenaAllocator {
public:
    using value_type = T;
    static const size_t arena_size = N;

    explicit ArenaAllocator() {
        arena_ptr = static_cast<T*>(std::malloc(arena_size*sizeof(T)));
        if ( arena_ptr == nullptr )
            throw std::bad_alloc();
    };

    ~ArenaAllocator() {
        std::free(static_cast<void*>(arena_ptr));
    }

    template <typename T2, size_t N2>
    explicit ArenaAllocator(const ArenaAllocator<T2, N2> &) {
    }

    template <typename T2>
    struct rebind {
        using other = ArenaAllocator<T2, N>;
    };

    T* allocate(std::size_t n) {

        arena_position++;
        if ( arena_position >= N )
            throw std::runtime_error("memory limit is exceeded");

        return &arena_ptr[arena_position];
    }

    void deallocate(T* p, std::size_t) {
    }

private:
    T* arena_ptr = nullptr;
    int arena_position = -1;
};

template <typename T>
void fill(T &m) {
    m[0] = 1;
    for ( int i = 1; i < 10; ++i )
        m[i] = m[i-1] * i;
}

template <typename T>
void print(const T &m) {
    for (auto [k, v] : m) {
        std::cout << k << " " << v << std::endl;
    }
}

int main() {

    std::map<int, int, std::less<>> m1;
    fill(m1);

    std::map<int, int, std::less<>, ArenaAllocator<std::pair<const int, int>, 10>> m2;
    fill(m2);
    print(m2);

    return 0;
}
