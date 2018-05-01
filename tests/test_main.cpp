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
    "\n";

    std::string out_data =
    "bulk: cmd1, cmd2\n"
    "bulk: cmd3\n";

    test_prosess("2", in_data, out_data);
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
    "}\n"
    "cmd7\n"
    "cmd8\n"
    "{\n"
    "cmd9\n"
    "cmd10\n"
    "\n";

    std::string out_data =
    "bulk: cmd1, cmd2\n"
    "bulk: cmd3\n"
    "bulk: cmd4, cmd5, cmd6\n"
    "bulk: cmd7, cmd8\n";

    test_prosess("2", in_data, out_data);
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
    "}\n";

    std::string out_data =
    "bulk: cmd1, cmd2, cmd3, cmd4, cmd5, cmd6\n";

    test_prosess("2", in_data, out_data);
}


BOOST_AUTO_TEST_CASE(invalid_bulk_1)
{
    std::string  in_data = 
    "cmd1\n"
    "}\n"
    "cmd3\n"
    "cmd4\n"
    "{\n"
    "\n"
    "{\n"
    "cmd5\n"
    "cmd6\n"
    "}\n";

    std::string out_data =
    "bulk: cmd5, cmd6\n";

    test_prosess("2", in_data, out_data);
}

BOOST_AUTO_TEST_CASE(invalid_bulk_2)
{
    std::string  in_data = 
    "cmd1\n"
    "\n"
    "}\n"
    "cmd3\n"
    "cmd4\n"
    "{\n"
    "\n"
    "{\n"
    "cmd5\n"
    "cmd6\n"
    "}\n";

    std::string out_data =
    "bulk: cmd1\n"
    "bulk: cmd5, cmd6\n";

    test_prosess("2", in_data, out_data);
}


BOOST_AUTO_TEST_CASE(invalid_bulk_3)
{
    std::string  in_data = 
    "cmd1\n" 
    "cmd2\n"
    "{\n" 
    "cmd3\n"
    "cmd4\n" 
    "\n"
    "cmd5\n"
    "cmd6\n";

    std::string out_data =
    "bulk: cmd1, cmd2\n"
    "bulk: cmd5, cmd6\n";

    test_prosess("2", in_data, out_data);
}

BOOST_AUTO_TEST_SUITE_END()