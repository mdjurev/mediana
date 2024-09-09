cmake_minimum_required(VERSION 3.24)

project(Mediana VERSION 1.0 LANGUAGES CXX)

function(set_compiler_options TARGET_NAME)
	set_property(TARGET ${TARGET_NAME} PROPERTY COMPILE_WARNING_AS_ERROR ON)
	if(MSVC)
		target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
		target_compile_options(${TARGET_NAME} PRIVATE /wd4100) #unreferenced formal parameter
		target_compile_options(${TARGET_NAME} PRIVATE /wd4189) #local variable is initialized but not referenced
	else()
		target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
	endif()
endfunction()


set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

add_library(med INTERFACE include/med.h)
target_include_directories(med INTERFACE include)


option (MED_BENCHMARK "Enable benchmarking executable" ON)
if(MED_BENCHMARK)
	add_executable(Benchmark 
		benchmark/bench.cpp
	)
	target_link_libraries(Benchmark PRIVATE med)
	set_compiler_options(Benchmark)
endif()


option(MED_TESTS "Unit tests with Doctest" ON)
if(MED_TESTS)
	option(DOCTEST_NO_INSTALL "" ON)
	add_subdirectory(tests)
	set_compiler_options(tests)
endif()