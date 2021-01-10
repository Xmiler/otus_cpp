#include <iostream>
#include <unordered_map>

namespace otus {

    template <typename T, T N,
              typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
    class SparseMatrix {
        const static T default_value = N;

    public:
        SparseMatrix() = default;
        ~SparseMatrix() = default;

        using key_t=std::tuple<size_t, size_t>;
        struct key_hash : public std::unary_function<key_t, size_t> {
            size_t operator()(const key_t& key) const {
                return std::get<0>(key) ^ std::get<1>(key);
            }
        };
        using map_t=std::unordered_map<key_t, T, key_hash>;

        class Value {
        public:
            Value(SparseMatrix<T, N> *ptr_sparse_matrix, size_t y, size_t x) :
                    m_ptr_sparse_matrix(ptr_sparse_matrix), m_y(y), m_x(x) {};
            ~Value() = default;

            Value& operator=(const Value& value) {
                m_ptr_sparse_matrix->set_value(m_y, m_x, T(value));
                return *this;
            }

            Value& operator=(const T& v) {
                m_ptr_sparse_matrix->set_value(m_y, m_x, v);
                return *this;
            }

            operator T() const {
                return m_ptr_sparse_matrix->get_value(m_y, m_x);
            }

        private:
            SparseMatrix<T, N> *m_ptr_sparse_matrix;
            size_t m_y;
            size_t m_x;
        };

        class Row {
        public:
            Row(SparseMatrix<T, N> *ptr_sparse_matrix, size_t y) :
                    m_ptr_sparse_matrix(ptr_sparse_matrix), m_y(y){};
            ~Row() = default;

            Value operator[](size_t x) {
                return Value(m_ptr_sparse_matrix, m_y, x);
            }

            T operator[] (size_t x) const {
                return m_ptr_sparse_matrix->get_value(m_y, x);
            }

        private:
            SparseMatrix<T, N> *m_ptr_sparse_matrix;
            size_t m_y;
        };

        size_t size() const {
            return m_data.size();
        };

        Row operator[](size_t y) {
            return Row(this, y);
        }

        struct Iterator {
            using value_type=std::tuple<size_t, size_t, T>;
            using difference_type=std::ptrdiff_t;
            using pointer=value_type*;
            using reference=value_type&;
            using iterator_category=std::input_iterator_tag;

            explicit Iterator(typename map_t::const_iterator ptr) : m_ptr(ptr) {};
            value_type operator*() const { return std::make_tuple(std::get<0>(m_ptr->first), std::get<1>(m_ptr->first), m_ptr->second); }
            pointer operator->() { return m_ptr; }
            Iterator operator++() { m_ptr++; return *this; };
            Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; };
            friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

        private:
            typename map_t::const_iterator m_ptr;
        };

        Iterator begin() {
            return Iterator(m_data.begin());
        }

        Iterator end() {
            return Iterator(m_data.end());
        }

        void set_value(size_t y, size_t x, T value) {
            auto coords = std::make_tuple(y, x);
            auto it = m_data.find(coords);
            if (it == m_data.end() && value != default_value) {
                m_data[coords] = value;
            }
            else if (it != m_data.end()) {
                if (value == default_value)
                    m_data.erase(it->first);
                else
                    m_data[coords] = value;
            }
        }

        T get_value(size_t y, size_t x) const {
            auto it = m_data.find(std::make_tuple(y, x));
            if (it == m_data.end())
                return default_value;
            else
                return it->second;
        }

    private:
        map_t m_data;
    };

}
