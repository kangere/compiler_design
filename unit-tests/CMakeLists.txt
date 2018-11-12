project(tests CXX)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "-std=c++1z")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

add_executable(tests 
	../type.cpp
	../expr.cpp
	../decl.cpp
	../stmt.cpp
	../debug.cpp
	../s_expr.cpp
	../factory.cpp
	../builder.cpp
	../builder.util.cpp
	../symbol.cpp
	../location.cpp
	../token.cpp
	../lexer.cpp
	tests-main.cpp
	tests-expression.cpp
	tests-declarations.cpp
	tests-stmts.cpp
	tests-factory.cpp
	tests-lexer.cpp )