#include "lib.hpp"

int main() {

    otus::SparseMatrix<int, -1> matrix;

    std::cout << matrix.size() << std::endl;

    (matrix[100][100] = 314) = 413;

    std::cout << matrix[100][100] << std::endl;

    std::cout << matrix.size() << std::endl;

    for(const auto& [x, y, v] : matrix) {
        std::cout << x << y << v << std::endl;
    }
    return 0;
}
