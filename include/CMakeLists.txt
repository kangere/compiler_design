#library
add_library(include 
	type.cpp
	expr.cpp
	decl.cpp
	stmt.cpp
	debug.cpp
	s_expr.cpp
	factory.cpp
	builder.cpp
	builder.util.cpp
	symbol.cpp
	location.cpp
	token.cpp
	lexer.cpp
	parser.cpp
	parser.expr.cpp
	parser.stmt.cpp
	parser.decl.cpp
	actions.cpp
	scope.cpp)

#Link library
target_include_directories(include PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})