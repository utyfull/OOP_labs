cmake_minimum_required(VERSION 3.20)

project(Lab6)

add_executable(lab6 main.cpp include/lab6.h src/lab6.cpp)

target_include_directories(lab6 PRIVATE include)
