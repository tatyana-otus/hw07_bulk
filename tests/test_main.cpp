#include "lib.h"
#include <sstream>
#include "functions.h"


#define BOOST_TEST_MODULE test_main

#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp> 
#include <boost/test/output_test_stream.hpp>

using boost::test_tools::output_test_stream;


void test_prosess(const char* N, std::string in_data, std::string out_data)
{
    std::stringstream iss;
    std::stringstream oss;

    iss << in_data;
    prosess(N, iss, oss);

    BOOST_CHECK_EQUAL( oss.str(), out_data );

}


BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_version_valid)
{
    BOOST_CHECK( (major_version() >= 0) &&  (minor_version() >= 0) && (patch_version() >= 0) );
    BOOST_CHECK( (major_version() >  0) ||  (minor_version() >  0) || (patch_version() >  0) );
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(test_suite_bulk)


BOOST_AUTO_TEST_CASE(base_invalid_input)
{
    BOOST_CHECK_THROW(prosess("-1"),  std::invalid_argument);
    BOOST_CHECK_THROW(prosess("0"),   std::invalid_argument);
    BOOST_CHECK_THROW(prosess("0x10"),std::invalid_argument);
    BOOST_CHECK_THROW(prosess("a34"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(empty_bulk)
{
   
    std::string  in_data = ""; 
    std::string out_data = "";

    test_prosess("2", in_data, out_data);
}

BOOST_AUTO_TEST_CASE(static_bulk)
{  
    std::string  in_data = 
    "cmd1\n"
    "cmd2\n"
    "cmd3\n"
    "cmd4\n"
    "cmd5"; 

    std::string out_data =
    "bulk: cmd1, cmd2, cmd3\n"
    "bulk: cmd4, cmd5\n";

    test_prosess("3", in_data, out_data);
}


BOOST_AUTO_TEST_CASE(dinamic_bulk)
{
    std::string  in_data =  
    "cmd1\n"
    "cmd2\n"
    "cmd3\n"
    "{\n"
    "cmd4\n"
    "cmd5\n"
    "cmd6\n"
    "cmd7\n"
    "}";

    std::string out_data =
    "bulk: cmd1, cmd2, cmd3\n"
    "bulk: cmd4, cmd5, cmd6, cmd7\n";

    test_prosess("3", in_data, out_data);
}


BOOST_AUTO_TEST_CASE(dinamic_enclosed_bulk)
{ 
    std::string  in_data = 
    "{\n"
    "cmd1\n"
    "cmd2\n"
    "{\n"
    "cmd3\n"
    "cmd4\n"
    "}\n"
    "cmd5\n"
    "cmd6\n"
    "}";  

    std::string out_data =
    "bulk: cmd1, cmd2, cmd3, cmd4, cmd5, cmd6\n";

    test_prosess("3", in_data, out_data);
}


BOOST_AUTO_TEST_CASE(incomplete_dinamic_bulk)
{
    std::string  in_data = 
        "cmd1\n"
        "cmd2\n"
        "cmd3\n"
        "{\n"
        "cmd4\n"
        "cmd5\n"
        "cmd6\n"
        "cmd7";

    std::string out_data =
    "bulk: cmd1, cmd2, cmd3\n";

    test_prosess("3", in_data, out_data);
}


BOOST_AUTO_TEST_CASE(cmd_stream)
{
    std::string  in_data = 
        "cmd1\n"
        "cmd2\n"
        "cmd3\n"
        "{\n"
        "cmd4\n"
        "{\n"
        "cmd5\n"
        "}\n"
        "}\n"
        "cmd6\n"
        "cmd7\n"
        "cmd8";

    std::string out_data =
    "bulk: cmd1, cmd2\n"
    "bulk: cmd3\n"
    "bulk: cmd4, cmd5\n"
    "bulk: cmd6, cmd7\n"
    "bulk: cmd8\n";

    test_prosess("2", in_data, out_data);
}


BOOST_AUTO_TEST_CASE(wrong_cmd_stream)
{
    std::string  in_data = 
        "}\n"
        "cmd1\n"
        "cmd2\n"
        "cmd3\n"
        "{\n";

    std::string out_data = "";    

    BOOST_CHECK_THROW(test_prosess("2", in_data, out_data),  std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()