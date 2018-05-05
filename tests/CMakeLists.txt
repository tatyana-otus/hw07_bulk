project(test)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_main_cli test_main.cpp)

target_include_directories(test_main_cli PRIVATE ../include)
target_include_directories(test_main_cli PRIVATE ${Boost_INCLUDE_DIR})

set_target_properties(test_main_cli PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)

target_link_libraries(test_main_cli
  ${Boost_LIBRARIES}
  version
)

enable_testing()

add_test(test_version_valid           test_main_cli -t test_suite_main/test_version_valid)
add_test(test_base_invalid_input      test_main_cli -t test_suite_bulk/base_invalid_input)
add_test(test_empty_bulk              test_main_cli -t test_suite_bulk/empty_bulk)
add_test(test_static_bulk             test_main_cli -t test_suite_bulk/static_bulk)
add_test(test_dinamic_bulk            test_main_cli -t test_suite_bulk/dinamic_bulk)
add_test(test_dinamic_enclosed_bulk   test_main_cli -t test_suite_bulk/dinamic_enclosed_bulk)
add_test(test_incomplete_dinamic_bulk test_main_cli -t test_suite_bulk/incomplete_dinamic_bulk)
add_test(test_cmd_stream              test_main_cli -t test_suite_bulk/cmd_stream)
add_test(test_wrong_cmd_stream        test_main_cli -t test_suite_bulk/wrong_cmd_stream)