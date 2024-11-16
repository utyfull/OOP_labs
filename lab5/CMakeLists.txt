cmake_minimum_required(VERSION 3.20)

project(Lab5)

add_executable(lab5 src/lab5.cpp main.cpp)

target_include_directories(lab5 PRIVATE include)
