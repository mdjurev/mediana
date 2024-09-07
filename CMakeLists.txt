cmake_minimum_required(VERSION 3.19)

project(Mediana VERSION 1.0 LANGUAGES CXX)

add_library(med INTERFACE include/med.h)
target_include_directories(med INTERFACE include)


option (MED_BENCHMARK "Enable benchmarking executable" ON)
if(MED_BENCHMARK)
	add_executable(Benchmark 
		benchmark/bench.cpp
	)
	target_link_libraries(Benchmark PRIVATE med)
endif()


option(MED_TESTS "Unit tests with Doctest" ON)
if(MED_TESTS)
	option(DOCTEST_NO_INSTALL "" ON)
	add_subdirectory(tests)
endif()