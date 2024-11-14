#include <benchmark/benchmark.h>
#include "myListKV.hpp"
#include "myArray.hpp"
#include "myHashMap.hpp"
#include <string>
#include <cstdlib>

void suppressOutput() {
    std::cout.setstate(std::ios::failbit);
}

void restoreOutput() {
    std::cout.clear();
}

// ==== Benchmarks for MyList ====

static void BM_MyList_PushBack(benchmark::State& state) {
    MyList<int, int> list;
    
    for (auto _ : state) {
        list.push_back(1, 42);  // Добавляем элемент с ключом и значением
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyList_PushBack)->Range(1 << 10, 1 << 20)->Complexity();

static void BM_MyList_Find(benchmark::State& state) {
    MyList<int, int> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i, i);  // Заполняем список
    }
    for (auto _ : state) {
        int value;
        list.find(state.range(0) / 2, value);  // Поиск элемента в середине
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyList_Find)->Range(1 << 10, 1 << 20)->Complexity();

static void BM_MyList_Remove(benchmark::State& state) {
    MyList<int, int> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i, i);  // Заполняем список
    }
    for (auto _ : state) {
        list.remove(state.range(0) / 2);  // Удаляем элемент из середины
        list.push_back(state.range(0), 42);  // Восстанавливаем элемент, чтобы длина оставалась постоянной
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyList_Remove)->Range(1 << 10, 1 << 20)->Complexity();

// ==== Benchmarks for MyArray ====

static void BM_MyArray_Mpush(benchmark::State& state) {
    MyArray<int> arr;
    for (auto _ : state) {
        arr.MPUSH(42);  // Добавляем элемент в массив
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_Mpush)->Range(1 << 10, 1 << 20)->Complexity();

static void BM_MyArray_MpushAtIndex(benchmark::State& state) {
    MyArray<int> arr;
    for (int i = 0; i < state.range(0); i++) {
        arr.MPUSH(42);
    }
    for (auto _ : state) {
        arr.MPUSH(state.range(0) / 2, 99);  // Добавление в середину
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_MpushAtIndex)->Range(1 << 10, 1 << 20)->Complexity();

static void BM_MyArray_Mdel(benchmark::State& state) {
    MyArray<int> arr;
    for (int i = 0; i < state.range(0); i++) {
        arr.MPUSH(42);  // Заполняем массив
    }
    for (auto _ : state) {
        arr.MDEL(state.range(0) / 2);  // Удаляем из середины
        arr.MPUSH(42);  // Восстанавливаем элемент, чтобы длина оставалась постоянной
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_Mdel)->Range(1 << 10, 1 << 20)->Complexity();

static void BM_MyArray_Mget(benchmark::State& state) {
    MyArray<int> arr;
    for (int i = 0; i < state.range(0); i++) {
        arr.MPUSH(i);  // Заполняем массив
    }
    for (auto _ : state) {
        benchmark::DoNotOptimize(arr.MGET(state.range(0) / 2));  // Доступ к элементу в середине
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_Mget)->Range(1 << 10, 1 << 20)->Complexity();

static void BM_MyArray_Mreset(benchmark::State& state) {
    MyArray<int> arr;
    for (int i = 0; i < state.range(0); i++) {
        arr.MPUSH(i);  // Заполняем массив
    }
    for (auto _ : state) {
        arr.MRESET(state.range(0) / 2, 99);  // Замена элемента в середине
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_MyArray_Mreset)->Range(1 << 10, 1 << 20)->Complexity();

// ==== Benchmarks for MyHashMap ====

MyHashMap<std::string, int> hashmap(100);

static void BM_HashMap_Insert(benchmark::State& state) {
    for (auto _ : state) {
        hashmap.clear();
        for (int i = 0; i < state.range(0); ++i) {
            hashmap.HSET("key" + std::to_string(i), i);
        }
    }
}
BENCHMARK(BM_HashMap_Insert)->Range(8, 1 << 8)->Complexity();

static void BM_HashMap_Get(benchmark::State& state) {
    hashmap.clear();
    for (int i = 0; i < state.range(0); ++i) {
        hashmap.HSET("key" + std::to_string(i), i);
    }
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            int value = hashmap.HGET("key" + std::to_string(i));
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK(BM_HashMap_Get)->Range(8, 1 << 8)->Complexity();

static void BM_HashMap_Delete(benchmark::State& state) {
    hashmap.clear();
    suppressOutput();
    for (int i = 0; i < state.range(0); ++i) {
        hashmap.HSET("key" + std::to_string(i), i);
    }
    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            hashmap.HDEL("key" + std::to_string(i));
        }
    }
    restoreOutput();
} 
BENCHMARK(BM_HashMap_Delete)->Range(8, 1 << 8)->Complexity();

static void BM_HashMap_SaveToFile(benchmark::State& state) {
    hashmap.clear();
    for (int i = 0; i < state.range(0); ++i) {
        hashmap.HSET("key" + std::to_string(i), i);
    }
    for (auto _ : state) {
        hashmap.saveToFile("hashmap_data.txt");
    }
}
BENCHMARK(BM_HashMap_SaveToFile)->Range(8, 1 << 8)->Complexity();

static void BM_HashMap_LoadFromFile(benchmark::State& state) {
    hashmap.clear();
    for (int i = 0; i < state.range(0); ++i) {
        hashmap.HSET("key" + std::to_string(i), i);
    }
    hashmap.saveToFile("hashmap_data.txt");
    for (auto _ : state) {
        hashmap.clear();
        hashmap.loadFromFile("hashmap_data.txt");
    }
}
BENCHMARK(BM_HashMap_LoadFromFile)->Range(8, 1 << 8)->Complexity();

// ==== Main Function to Run All Benchmarks ====

BENCHMARK_MAIN();

