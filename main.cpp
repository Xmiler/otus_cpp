#include <iostream>
#include <memory>
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

    template <typename U, typename ...Args>
    void construct(U* p, Args &&...args) {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
        p->~T();
    }

private:
    T* arena_ptr = nullptr;
    int arena_position = -1;
};

template <typename T>
void fill_map(T &m) {
    m[0] = 1;
    for ( int i = 1; i < 10; ++i )
        m[i] = m[i-1] * i;
}

template <typename T>
void print_map(const T &m) {
    for (auto [k, v] : m) {
        std::cout << k << " " << v << std::endl;
    }
}

template <typename T>
void fill_list(T &l) {
    l.push_back(1);
    for ( int i = 1; i < 10; ++i ) {
        l.push_back(l.back()*i);
    }
}

template <typename T>
void print_list(const T &l) {
    for ( const int &el : l ) {
        std::cout << el << std::endl;
    }
}

namespace otus {

    template<typename T, typename Alloc=std::allocator<T>>
    class list {
        struct Node {
            explicit Node(T value_) : value(std::move(value_)) {}

            T value;
            Node *next;
        };

        class const_iterator {
        public:
            explicit const_iterator(Node* ptr) : ptr_(ptr) {}
            const_iterator operator++() { auto tmp_ = ptr_; ptr_=ptr_->next; return const_iterator(tmp_); };
            const_iterator operator++(int) { ptr_=ptr_->next; return *this; };
            bool operator!=(const const_iterator &other) { return other.ptr_ != this->ptr_; };
            const T* operator->() { return &ptr_->value; };
            const T& operator*() { return ptr_->value; }
        private:
            Node *ptr_;
        };

    public:
        using _Tp_alloc_type = typename Alloc::template rebind<Node>::other;

        list() = default;
        ~list() {
            for ( Node* ptr_iter = ptr_head; ptr_iter != nullptr; ) {
                auto ptr_iter_ = ptr_iter->next;
                allocator.destroy(ptr_iter);
                allocator.deallocate(ptr_iter, 1);
                ptr_iter = ptr_iter_;
            }
        }

        const_iterator begin() const {
            return const_iterator(ptr_head);
        }

        const_iterator end() const {
            return const_iterator(nullptr);
        }

        T back() {
            return ptr_tail->value;
        }

        void push_back(T el) {

            auto ptr_new = allocator.allocate(1);
            allocator.construct(ptr_new, std::move(el));

            if (ptr_head == nullptr) {
                ptr_head = ptr_new;
                ptr_tail = ptr_head;
            }
            else {
                ptr_tail->next = ptr_new;
                ptr_tail = ptr_new;
            }
        }

    private:
        Node* ptr_head = nullptr;
        Node* ptr_tail = nullptr;
        _Tp_alloc_type allocator;
    };
}

int main() {

    std::map<int, int, std::less<>> m1;
    fill_map(m1);

    std::map<int, int, std::less<>, ArenaAllocator<std::pair<const int, int>, 10>> m2;
    fill_map(m2);
    print_map(m2);

    otus::list<int> l1;
    fill_list(l1);

    otus::list<int, ArenaAllocator<int, 10>> l2;
    fill_list(l2);
    print_list(l2);

    return 0;
}
