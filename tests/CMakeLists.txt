cmake_minimum_required(VERSION 3.20)
project(Tests)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(test_lab1 lab1_test.cpp)
target_link_libraries(test_lab1 PRIVATE GTest::GTest)
target_include_directories(test_lab1 PRIVATE ../lab1/include)
add_test(NAME test_lab1 COMMAND test_lab1)
