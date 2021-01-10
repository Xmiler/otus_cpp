#include "lib.hpp"

int main() {

    otus::SparseMatrix<int, 0> matrix;

    constexpr int num = 10;
    for (int i = 1; i < num; i++)
        matrix[i][i] = matrix[num-i-1][i] = i;

    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++) {
            printf("%i ", int(matrix[i][j]));
        }
        printf("\n");
    }
    printf("\nCount of occupied cells: %zu\n", matrix.size());

    printf("\nThese cells are:\n");
    for (const auto& [x, y, v] : matrix) {
        printf("matrix[%zu][%zu]=%i\n", x, y, v);
    }

    return 0;
}
