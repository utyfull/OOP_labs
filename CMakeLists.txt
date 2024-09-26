cmake_minimum_required(VERSION 3.20)

project(OS_LABS C CXX)

enable_testing()

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

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



