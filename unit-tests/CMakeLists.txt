add_executable(tests 
	tests-main.cpp
	tests-expression.cpp
	tests-declarations.cpp
	tests-stmts.cpp
	tests-factory.cpp
	tests-lexer.cpp
	tests-parser.cpp )

target_link_libraries(tests LINK_PUBLIC include)

add_custom_command(TARGET tests POST_BUILD 
					COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/sam.mc $<TARGET_FILE_DIR:tests>
					COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/nums.mc $<TARGET_FILE_DIR:tests>
					COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/expressions.mc $<TARGET_FILE_DIR:tests>
					COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/declarations.mc $<TARGET_FILE_DIR:tests>)