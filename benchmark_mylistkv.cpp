#include "myListKV.hpp"
#include <benchmark/benchmark.h>

static void BM_PushBack(benchmark::State& state) {
    MyList<int, std::string> list;
    for (auto _ : state) {
        list.push_back(state.range(0), "value");
    }
}
BENCHMARK(BM_PushBack)->Range(8, 8<<10);

static void BM_Find(benchmark::State& state) {
    MyList<int, std::string> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i, "value");
    }
    std::string value;
    for (auto _ : state) {
        benchmark::DoNotOptimize(list.find(state.range(0) / 2, value));
    }
}
BENCHMARK(BM_Find)->Range(8, 8<<10);

static void BM_Remove(benchmark::State& state) {
    MyList<int, std::string> list;
    for (int i = 0; i < state.range(0); ++i) {
        list.push_back(i, "value");
    }
    for (auto _ : state) {
        list.remove(state.range(0) / 2);
    }
}
BENCHMARK(BM_Remove)->Range(8, 8<<10);

BENCHMARK_MAIN();