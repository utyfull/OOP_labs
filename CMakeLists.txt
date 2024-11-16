cmake_minimum_required(VERSION 3.20)

project(OS_LABS C CXX)

enable_testing()

include(FindThreads)
include(FetchContent)



FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.12.1.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true  
)

FetchContent_MakeAvailable(googletest)

add_subdirectory(lab1)
add_subdirectory(tests)



