add_executable(sample 
			sample.cpp)

#link the executable
target_link_libraries(sample LINK_PUBLIC include)