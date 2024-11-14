# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(MyListBenchmark)

set(CMAKE_CXX_STANDARD 17)

# Добавляем Google Benchmark
find_package(benchmark REQUIRED)

add_executable(mylist_benchmark mylist_benchmark.cpp)
target_link_libraries(mylist_benchmark benchmark::benchmark pthread)
