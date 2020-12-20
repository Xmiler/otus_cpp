#define BOOST_TEST_MODULE tests

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(tests)

BOOST_AUTO_TEST_CASE (dummy) {
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_SUITE_END();