cmake_minimum_required(VERSION 3.15)

set (SOURCES
	testmain.cpp
)

add_executable(tests ${SOURCES})
target_link_libraries(tests PRIVATE med)