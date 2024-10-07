cmake_minimum_required(VERSION 3.20)
project(Tests)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(test_lab1 lab1_test.cpp ../lab1/main.cpp ../lab1/src/lab1.cpp ../lab1/include/lab1.h)
target_link_libraries(test_lab1 PRIVATE GTest::GTest)
target_include_directories(test_lab1 PRIVATE ../lab1/include)
add_test(NAME test_lab1 COMMAND test_lab1)

add_executable(test_lab2 lab2_test.cpp ../lab2/src/lab2.cpp ../lab2/include/lab2.h)
target_link_libraries(test_lab2 PRIVATE GTest::GTest)
target_include_directories(test_lab2 PRIVATE ../lab2/include)
add_test(NAME test_lab2 COMMAND test_lab2)
