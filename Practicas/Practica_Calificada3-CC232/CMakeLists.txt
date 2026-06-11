cmake_minimum_required(VERSION 3.10)

project(Practica3_CC232_SkewHeap)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(solucion_pc3 src/main.cpp src/skew_heap.cpp)
add_executable(demo_video demos/demo_merge_skew.cpp src/skew_heap.cpp)

enable_testing()
add_executable(test_skew_heap tests/test_skew_heap.cpp src/skew_heap.cpp)
add_test(NAME PruebaInvarianteSkew COMMAND test_skew_heap)

enable_testing()
add_test(NAME TestSkewHeap COMMAND test_skew_heap)