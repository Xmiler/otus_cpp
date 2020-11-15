#include <iostream>
#include <map>
#include <vector>

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

namespace otus {

    template<typename T>
    class List {
        struct Node {
            explicit Node(T value_) : value(std::move(value_)) {}

            T value;
            Node *next;
        };

        class const_iterator {
        public:
            explicit const_iterator(Node* ptr) : ptr_(ptr) {}
            const_iterator operator++(int) { ptr_=ptr_->next; return *this; };
            const Node* operator->() { return ptr_; };
        private:
            Node *ptr_;
        };

    public:

        List() = default;
        ~List() {
            for ( Node* ptr_iter = ptr_head; ptr_iter != nullptr; ) {
                auto ptr_iter_ = ptr_iter->next;
                delete ptr_iter;
                ptr_iter = ptr_iter_;
            }
        }

        const_iterator cbegin() const {
            return const_iterator(ptr_head);
        }

        const_iterator cend() const {
            return const_iterator(ptr_tail);
        }

        void push_back(T el) {
            Node *ptr_new = new Node(std::move(el));
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
    };
}

int main() {

    std::map<int, int, std::less<>> m1;
    fill(m1);

    std::map<int, int, std::less<>, ArenaAllocator<std::pair<const int, int>, 10>> m2;
    fill(m2);
    print(m2);

    otus::List<int> l1;
    l1.push_back(1);

    return 0;
}
