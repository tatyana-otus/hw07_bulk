#include "lib.h"
#include <limits>

#define BOOST_TEST_MODULE test_main

#include "test_helper.h"


BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_version_valid)
{
    BOOST_CHECK( (major_version() >= 0) &&  (minor_version() >= 0) && (patch_version() >= 0) );
    BOOST_CHECK( (major_version() >  0) ||  (minor_version() >  0) || (patch_version() >  0) );
}




BOOST_AUTO_TEST_CASE(base_invalid_input)
{
    BOOST_CHECK_THROW(prosess("-1"),  std::invalid_argument);
    BOOST_CHECK_THROW(prosess("0"),   std::invalid_argument);
    BOOST_CHECK_THROW(prosess("0x10"),std::invalid_argument);
    BOOST_CHECK_THROW(prosess("a34"), std::invalid_argument);

    auto str_1 = std::to_string(std::numeric_limits<unsigned long long>::max() + 1);
    BOOST_CHECK_THROW(test_prosess(str_1.c_str(), "", ""), std::invalid_argument);

    std::vector<std::string> v;
    auto str_2 = std::to_string(v.max_size() + 1 );
    BOOST_CHECK_THROW(test_prosess(str_2.c_str(), "", ""), std::length_error);

    auto str_3 = std::to_string(v.max_size() );
    BOOST_CHECK_THROW(test_prosess(str_3.c_str(), "", ""), std::bad_alloc);

}



BOOST_AUTO_TEST_SUITE_END()