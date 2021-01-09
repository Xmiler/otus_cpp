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

        [[nodiscard]]
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

        int64_t size() {
            return m_data.size();
        };

        SparseMatrixRow<T> operator[](int64_t y) {
            return SparseMatrixRow<T>(this, y);
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
        using key_t=std::tuple<int64_t, int64_t>;
        struct key_hash : public std::unary_function<key_t, size_t> {
            size_t operator()(const key_t& key) const {
                return std::get<0>(key) ^ std::get<1>(key);
            }
        };
        std::unordered_map<key_t, T, key_hash> m_data;
        T m_default_value;
    };
}

int main() {


    otus::SparseMatrix<int> smt;

    std::cout << smt[0][100] << std::endl;
    smt[0][100] = 1;
    std::cout << smt[0][100] << std::endl;
    smt[0][100] = 0;
    std::cout << smt[0][100] << std::endl;

    return 0;
}
