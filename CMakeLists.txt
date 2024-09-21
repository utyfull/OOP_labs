cmake_minimum_required(VERSION 3.20)
project(OOP_LABS C CXX)

enable_testing()
add_subdirectory(tests)
add_subdirectory(external/googletest)

if (MSVC)
    add_compile_options(/W4 /WX)
else() 
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include(FindThreads)

add_subdirectory(lab1)



