#include <chrono>
#include <thread>

#define BOOST_TEST_MODULE test_main

#include "test_helper.h"
#include <fstream>

BOOST_AUTO_TEST_SUITE(test_suite_log)


BOOST_AUTO_TEST_CASE(log_file_creation)
{  
    std::stringstream ess;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    one_cmd1_pass(ess);
    BOOST_CHECK_EQUAL( ess.str(), "" );

    std::this_thread::sleep_for(std::chrono::seconds(1));

    one_cmd1_pass(ess);
    BOOST_CHECK_EQUAL( ess.str(), "" );
}


BOOST_AUTO_TEST_CASE(log_file_content)
{  
    std::stringstream ess;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    BOOST_CHECK( ess.str().size() == 0 );

    one_cmd1_pass(ess);
    one_cmd1_pass(ess);

    BOOST_CHECK( ess.str().size() > 0 ); 

    //getting the filename from the string "*.log log file already exists"
    std::string file_name = ess.str().substr (0, ess.str().find(" ")); 

    std::ifstream file{file_name};
    BOOST_CHECK_EQUAL( file.good(), true );

    std::stringstream buffer;
    buffer << file.rdbuf();

    BOOST_CHECK_EQUAL( buffer.str(), "bulk: cmd1" );

    file.close();
}

BOOST_AUTO_TEST_SUITE_END()