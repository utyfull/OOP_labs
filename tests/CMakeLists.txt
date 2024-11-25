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

add_executable(test_lab3 lab3_test.cpp ../lab3/src/lab3.cpp ../lab3/include/lab3.h)
target_link_libraries(test_lab3 PRIVATE GTest::GTest)
target_include_directories(test_lab3 PRIVATE ../lab3/include)
add_test(NAME test_lab3 COMMAND test_lab3)


add_executable(test_lab6 lab6_test.cpp ../lab6/src/lab6.cpp ../lab6/include/lab6.h)
target_link_libraries(test_lab6 PRIVATE GTest::GTest)
target_include_directories(test_lab6 PRIVATE ../lab6/include)
add_test(NAME test_lab6 COMMAND test_lab6)
