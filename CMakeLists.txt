cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic")

project(Variant LANGUAGES CXX VERSION 1.0.0)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)