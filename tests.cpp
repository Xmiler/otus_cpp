#define BOOST_TEST_MODULE tests

#include "lib.hpp"
#include <unordered_set>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE (keep_empty) {

    constexpr int default_value = -1;

    otus::SparseMatrix<int, default_value> matrix;
    BOOST_CHECK_EQUAL(matrix.size(), 0);

    BOOST_CHECK_EQUAL(matrix[10][20], default_value);
    BOOST_CHECK_EQUAL(matrix[15][25], default_value);
    BOOST_CHECK_EQUAL(matrix[50][100], default_value);

    BOOST_CHECK_EQUAL(matrix.size(), 0);

}

BOOST_AUTO_TEST_CASE (fill_and_make_empty_again) {

    constexpr int default_value = -1;
    constexpr int num = 10;

    otus::SparseMatrix<int, default_value> matrix;
    BOOST_CHECK_EQUAL(matrix.size(), 0);

    for ( int i = 0; i < num; i++ )
        for ( int j = 0; j < num; j++ )
            matrix[i][j] = i*10+j;
    BOOST_CHECK_EQUAL(matrix.size(), num*num);

    for ( int i = 0; i < num; i++ )
        for (int j = 0; j < num; j++)
            BOOST_CHECK_EQUAL(matrix[i][j], i * 10 + j);
    BOOST_CHECK_EQUAL(matrix[num][num], default_value);

    for ( int i = 0; i < num; i++ )
        for (int j = 0; j < num; j++)
            matrix[i][j] = default_value;
    BOOST_CHECK_EQUAL(matrix.size(), 0);

}

BOOST_AUTO_TEST_CASE (canonical_assignment) {
    constexpr int default_value = -1;

    otus::SparseMatrix<int, default_value> matrix;

    ((matrix[11][22] = 1122) = 2211) = 3333;

    BOOST_CHECK_EQUAL(matrix[11][22], 3333);
    BOOST_CHECK_EQUAL(matrix.size(), 1);
}

BOOST_AUTO_TEST_CASE (check_itetator) {
    constexpr int default_value = -1;
    constexpr int num = 10;

    otus::SparseMatrix<int, default_value> matrix;
    std::unordered_set<int> memory;

    for ( int i = 0; i < num; i++ ) {
        matrix[i][i] = i;
        memory.insert(i*100+i*10+i);
    }
    BOOST_CHECK_EQUAL(memory.size(), num);


    for ( const auto& [x, y, v] : matrix )
        memory.erase(x*100+y*10+v);
    BOOST_CHECK_EQUAL(memory.size(), 0);
}
