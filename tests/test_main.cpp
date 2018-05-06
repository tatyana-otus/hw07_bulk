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


BOOST_AUTO_TEST_CASE(command_class)
{
    int count     = 0;
    int blk_size  = 0;
    const int N   = 4;
    
    struct Bulk_Count : public Handler
    {
        Bulk_Count(int& cnt_, int& size_):cnt(cnt_), size(size_) {}
       
        void on_bulk_resolved(const std::vector<std::string>& v, const time_t t = 0) override
        {
            ++cnt;
            size = v.size();
        } 
        int &cnt;
        int &size;
    };

     Command cmd {N};
     cmd.add_hanlder(std::make_unique<Bulk_Count>(count, blk_size));

     cmd.on_new_cmd("1");
     BOOST_CHECK_EQUAL( cmd.size(), 1 );
     BOOST_CHECK_EQUAL( count,      0 );
     BOOST_CHECK_EQUAL( blk_size,   0 );

     cmd.on_new_cmd("2");
     BOOST_CHECK_EQUAL( cmd.size(), 2 );
     BOOST_CHECK_EQUAL( count,      0 );
     BOOST_CHECK_EQUAL( blk_size,   0 );

     cmd.on_new_cmd("3");
     BOOST_CHECK_EQUAL( cmd.size(), 3 );
     BOOST_CHECK_EQUAL( count,      0 );
     BOOST_CHECK_EQUAL( blk_size,   0 );

     cmd.on_new_cmd("4");
     BOOST_CHECK_EQUAL( cmd.size(), 0 );
     BOOST_CHECK_EQUAL( count,      1 );
     BOOST_CHECK_EQUAL( blk_size,   N );
}

BOOST_AUTO_TEST_SUITE_END()