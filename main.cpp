#include <iostream>
#include <unordered_map>

namespace otus {

    template <typename T>
    class SparseMatrix;

    template <typename T>
    class SparseMatrixValue {
    public:
        explicit SparseMatrixValue(SparseMatrix<T> *ptr_sparse_matrix, int64_t x) :
            m_ptr_sparse_matrix(ptr_sparse_matrix), m_x(x) {};
        ~SparseMatrixValue() = default;

        SparseMatrixValue& operator=(T value) {
            m_ptr_sparse_matrix->add_value(m_x, value);
            return *this;
        }

        T get_value() const {
            return m_ptr_sparse_matrix->get_value(m_x);
        }

    private:
        SparseMatrix<T> *m_ptr_sparse_matrix;
        int64_t m_x;
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const SparseMatrixValue<T> &sparse_matrix_value) {
        os << sparse_matrix_value.get_value();
    }

    template <typename T>
    class SparseMatrix {
    public:
        SparseMatrix(T default_value = T(0)) : m_default_value(default_value) {};
        ~SparseMatrix() = default;

        int64_t size() {
            return m_data.size();
        };

        SparseMatrixValue<T> operator[](int64_t x) {
            return SparseMatrixValue<T>(this, x);
        }

        void add_value(int64_t x, T value) {
            auto it = m_data.find(x);
            if (it == m_data.end() && value != m_default_value) {
                m_data[x] = value;
            }
            else if (it != m_data.end() && value == m_default_value) {
                m_data.erase(it->first);
            }
        }

        T get_value(int64_t x) {
            auto it = m_data.find(x);
            if (it == m_data.end())
                return m_default_value;
            else
                return it->second;
        }

    private:
        std::unordered_map<int64_t, T> m_data;
        T m_default_value;
    };
}

int main() {

    otus::SparseMatrix<int> smt;

    std::cout << smt[100] << std::endl;
    smt[100] = 1;
    std::cout << smt[100] << std::endl;
    smt[100] = 0;
    std::cout << smt[100] << std::endl;

    return 0;
}
