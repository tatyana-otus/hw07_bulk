#include <chrono>
#include <thread>

#define BOOST_TEST_MODULE test_main

#include "test_helper.h"


BOOST_AUTO_TEST_SUITE(test_suite_log)


BOOST_AUTO_TEST_CASE(log)
{  
    std::stringstream ess;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    one_cmd_pass(ess);
    BOOST_CHECK_EQUAL( ess.str(), "" );

    std::this_thread::sleep_for(std::chrono::seconds(1));

    one_cmd_pass(ess);
    BOOST_CHECK_EQUAL( ess.str(), "" );

    one_cmd_pass(ess);
    BOOST_CHECK_EQUAL( ess.str(), "log file already exists\n" );  
}


BOOST_AUTO_TEST_SUITE_END()