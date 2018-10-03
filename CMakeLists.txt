project(ast CXX)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "-std=c++1z")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

add_executable(ast 
	test.cpp 
	type.cpp
	expr.cpp)