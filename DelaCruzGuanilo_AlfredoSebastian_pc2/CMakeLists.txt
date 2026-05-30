cmake_minimum_required(VERSION 3.10)
project(PC2_Number_Of_Atoms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Headers
include_directories(include)

# Solución 
add_library(solution_lib src/Solution.cpp)

# Tests
add_executable(run_tests tests/test_main.cpp)
target_link_libraries(run_tests solution_lib)

# Benchmark 
add_executable(run_benchmark benchmark/benchmark_main.cpp)
target_link_libraries(run_benchmark solution_lib)

# Demo 
add_executable(run_demo demos/demo_main.cpp)
target_link_libraries(run_demo solution_lib)