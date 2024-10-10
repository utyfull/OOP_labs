cmake_minimum_required(VERSION 3.20)

project(Lab3)

add_executable(lab3 main.cpp include/lab3.h src/lab3.cpp)

target_include_directories(lab3 PRIVATE include)
