#define BOOST_TEST_MODULE tests

#include "lib.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE (tutor_examples) {

    BOOST_CHECK_EQUAL(get_ip(char(-1)), "255");
    BOOST_CHECK_EQUAL(get_ip(short(0)), "0.0");
    BOOST_CHECK_EQUAL(get_ip(int(2130706433)), "1.0.0.127");
    BOOST_CHECK_EQUAL(get_ip(int(8875824491850138409)), "41.131.112.101");
    BOOST_CHECK_EQUAL(get_ip(std::string("8.8.8.8")), "8.8.8.8");
    BOOST_CHECK_EQUAL(get_ip(std::vector<int>{1,2,3,4}), "1.2.3.4");
    BOOST_CHECK_EQUAL(get_ip(std::list<int>{10,20,30,40}), "10.20.30.40");

}
