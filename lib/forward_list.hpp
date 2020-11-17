#pragma once

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