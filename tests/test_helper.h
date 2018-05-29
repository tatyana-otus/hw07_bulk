#include <chrono>
#include <thread>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp> 
#include <boost/test/output_test_stream.hpp>
#include "functions.h"

using boost::test_tools::output_test_stream;

void test_prosess(const char* N, const std::string& in_data, const std::string& out_data)
{
    std::stringstream iss;
    std::stringstream oss;

    iss << in_data;
    prosess(N, iss, oss);

    BOOST_CHECK_EQUAL( oss.str(), out_data );
}


void one_cmd1_pass(std::stringstream& err_stream)
{
    std::stringstream iss;
    std::stringstream oss;

    iss << "cmd1\n";
    prosess("1", iss, oss, err_stream);
}