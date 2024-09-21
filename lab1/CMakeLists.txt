cmake_minimum_required(VERSION 3.20)

project(Lab1)

add_executable(lab1 main.cpp include/lab1.h src/lab1.cpp)

target_include_directories(lab1 PRIVATE include)
