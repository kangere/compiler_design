cmake_minimum_required(VERSION 3.5)

project(cmp CXX)



set(CMAKE_CXX_FLAGS "-std=c++1z")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

add_subdirectory(include)
add_subdirectory(unit-tests)
add_subdirectory(src)
