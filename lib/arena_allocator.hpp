#pragma once

#include <memory>

namespace otus {

    template<typename T, size_t N>
    class ArenaAllocator {
    public:
        using value_type = T;
        static const size_t arena_size = N;

        explicit ArenaAllocator() {
            arena_ptr = static_cast<T *>(std::malloc(arena_size * sizeof(T)));
            if (arena_ptr == nullptr)
                throw std::bad_alloc();
        };

        ~ArenaAllocator() {
            std::free(static_cast<void *>(arena_ptr));
        }

        template<typename T2, size_t N2>
        explicit ArenaAllocator(const ArenaAllocator<T2, N2> &) {
        }

        template<typename T2>
        struct rebind {
            using other = ArenaAllocator<T2, N>;
        };

        T *allocate(std::size_t n) {

            arena_position++;
            if (arena_position >= N)
                throw std::runtime_error("memory limit is exceeded");

            return &arena_ptr[arena_position];
        }

        void deallocate(T *p, std::size_t) {
        }

        template<typename U, typename ...Args>
        void construct(U *p, Args &&...args) {
            new(p) U(std::forward<Args>(args)...);
        }

        void destroy(T *p) {
            p->~T();
        }

    private:
        T *arena_ptr = nullptr;
        int arena_position = -1;
    };
}
