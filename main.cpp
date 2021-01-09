#include <iostream>
#include <unordered_map>

namespace otus {

    template <typename T>
    class SparseMatrix;

    template <typename T>
    class SparseMatrixValue {
    public:
        SparseMatrixValue(SparseMatrix<T> *ptr_sparse_matrix, int64_t y, int64_t x) :
            m_ptr_sparse_matrix(ptr_sparse_matrix), m_y(y), m_x(x) {};
        ~SparseMatrixValue() = default;

        SparseMatrixValue& operator=(T value) {
            m_ptr_sparse_matrix->add_value(m_y, m_x, value);
            return *this;
        }

        T get_value() const {
            return m_ptr_sparse_matrix->get_value(m_y, m_x);
        }

    private:
        SparseMatrix<T> *m_ptr_sparse_matrix;
        int64_t m_y;
        int64_t m_x;
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const SparseMatrixValue<T> &sparse_matrix_value) {
        os << sparse_matrix_value.get_value();
        return os;
    }

    template <typename T>
    class SparseMatrixRow {
    public:
        SparseMatrixRow(SparseMatrix<T> *ptr_sparse_matrix, int64_t y) :
            m_ptr_sparse_matrix(ptr_sparse_matrix), m_y(y){};
        ~SparseMatrixRow() = default;

        SparseMatrixValue<T> operator[](int64_t x) {
            return SparseMatrixValue(m_ptr_sparse_matrix, m_y, x);
        }

    private:
        SparseMatrix<T> *m_ptr_sparse_matrix;
        int64_t m_y;
    };

    template <typename T>
    class SparseMatrix {
    public:
        explicit SparseMatrix(T default_value = T(0)) : m_default_value(default_value) {};
        ~SparseMatrix() = default;

        using key_t=std::tuple<int64_t, int64_t>;
        struct key_hash : public std::unary_function<key_t, size_t> {
            size_t operator()(const key_t& key) const {
                return std::get<0>(key) ^ std::get<1>(key);
            }
        };
        using map_t=std::unordered_map<key_t, T, key_hash>;

        size_t size() {
            return m_data.size();
        };

        SparseMatrixRow<T> operator[](int64_t y) {
            return SparseMatrixRow<T>(this, y);
        }

        struct Iterator {
            using value_type=std::tuple<int64_t, int64_t, T>;
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

        void add_value(int64_t y, int64_t x, T value) {
            auto coords = std::make_tuple(y, x);
            auto it = m_data.find(coords);
            if (it == m_data.end() && value != m_default_value) {
                m_data[coords] = value;
            }
            else if (it != m_data.end() && value == m_default_value) {
                m_data.erase(it->first);
            }
        }

        T get_value(int64_t y, int64_t x) {
            auto it = m_data.find(std::make_tuple(y, x));
            if (it == m_data.end())
                return m_default_value;
            else
                return it->second;
        }

    private:
        map_t m_data;
        T m_default_value;
    };
}

int main() {

    otus::SparseMatrix<int> matrix(-1);

    std::cout << matrix[0][0] << std::endl;
    std::cout << matrix.size() << std::endl;

    matrix[100][100] = 314;
    std::cout << matrix[100][100] << std::endl;

    std::cout << matrix.size() << std::endl;

    for(const auto c : matrix) {
        auto [x, y, v] = c;
        std::cout << x << y << v << std::endl;
    }

    return 0;
}
