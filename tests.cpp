#define BOOST_TEST_MODULE tests

#include "lib/handler.h"
#include "lib/logger.h"
#include <boost/test/unit_test.hpp>

std::string process(const std::string& input_str) {
    std::stringstream input, output;
    input << input_str;

    Handler handler(3);
    StandardLogger std_lgg(&handler, output);

    handler.process(input);

    return output.str();
}

BOOST_AUTO_TEST_CASE (whitout_nesting_and_devided_by_n) {

    std::string output_str = process("0\n1\n2\n3\n4\n5\n6\n7\n8");
    std::string expected_str = "0, 1, 2\n3, 4, 5\n6, 7, 8\n";

    BOOST_CHECK_EQUAL(output_str, expected_str);
}

BOOST_AUTO_TEST_CASE (without_nesting_and_not_devided_by_n) {

    std::string output_str = process("0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n");
    std::string expected_str = "0, 1, 2\n3, 4, 5\n6, 7, 8\n9, 10\n";

    BOOST_CHECK_EQUAL(output_str, expected_str);
}

BOOST_AUTO_TEST_CASE (with_single_nesting) {

    std::string output_str = process("0\n1\n{\n2\n3\n4\n5\n6\n}\n7\n8\n9\n10\n");
    std::string expected_str = "0, 1\n2, 3, 4, 5, 6\n7, 8, 9\n10\n";

    BOOST_CHECK_EQUAL(output_str, expected_str);
}

BOOST_AUTO_TEST_CASE (with_multiple_nesting) {

    std::string output_str = process("0\n1\n{\n2\n3\n{\n4\n5\n}\n6\n}\n7\n8\n9\n10\n");
    std::string expected_str = "0, 1\n2, 3, 4, 5, 6\n7, 8, 9\n10\n";

    BOOST_CHECK_EQUAL(output_str, expected_str);
}

BOOST_AUTO_TEST_CASE (with_multiple_nesting_interrupted) {

    std::string output_str = process("0\n1\n{\n2\n3\n{\n4\n5\n}\n6\n}\n7\n8\n{\n9\n10\n");
    std::string expected_str = "0, 1\n2, 3, 4, 5, 6\n7, 8\n";

    BOOST_CHECK_EQUAL(output_str, expected_str);
}

