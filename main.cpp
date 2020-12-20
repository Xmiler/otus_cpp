#include <iostream>
#include <unordered_map>

namespace otus {

    template <typename T>
    class SparseMatrix {
    public:
        SparseMatrix() = default;
        ~SparseMatrix() = default;

        int64_t size() {
            return data_.size();
        };

        T& operator[](int64_t x) {
            auto it = data_.find(x);
            if ( it == data_.end() ) {
                data_[x] = 0;
            }

            return data_[x];
        }

    private:
        std::unordered_map<int64_t, T> data_;
    };
}

int main() {

    otus::SparseMatrix<int> smt;

    std::cout << smt[100] << std::endl;
    smt[100] = 1;
    std::cout << smt[100] << std::endl;

    return 0;
}
