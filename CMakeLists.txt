cmake_minimum_required(VERSION 3.10)

project(MyListKVBenchmark)

# Устанавливаем стандарт C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем использование vcpkg
set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Добавляем библиотеку Google Benchmark
find_package(benchmark REQUIRED)

# Добавляем библиотеку Google Test
find_package(GTest REQUIRED)

# Добавляем исходный файл и бенчмарки
add_executable(MyListKVBenchmark benchmark_mylist.cpp)

# Линкуем с библиотеками Google Benchmark и Google Test
target_link_libraries(MyListKVBenchmark benchmark::benchmark GTest::GTest GTest::Main)