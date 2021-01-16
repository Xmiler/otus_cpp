#define BOOST_TEST_MODULE tests

#include "lib/handler.h"
#include "lib/logger.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE (whitout_nesting_and_devided_by_n) {

    std::stringstream input, output;
    input << "0\n1\n2\n3\n4\n5\n6\n7\n8";

    Handler handler(3);
    StandardLogger std_lgg(&handler, output);

    handler.process(input);

    std::string expected = "0, 1, 2\n3, 4, 5\n6, 7, 8\n";
    std::string output_str = output.str();

    BOOST_CHECK_EQUAL(output_str, expected);
}

BOOST_AUTO_TEST_CASE (without_nesting_and_not_devided_by_n) {

    std::stringstream input, output;
    input << "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n";

    Handler handler(3);
    StandardLogger std_lgg(&handler, output);

    handler.process(input);

    std::string expected = "0, 1, 2\n3, 4, 5\n6, 7, 8\n9, 10\n";
    std::string output_str = output.str();

    BOOST_CHECK_EQUAL(output_str, expected);
}