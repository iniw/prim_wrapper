#if defined(TESTS_BENCHMARK) && !defined(TESTS_ASSERTS)

#include "prim_wrapper.hpp"

#include <benchmark/benchmark.h>

static void bm_std_test1(benchmark::State& state) {
    for (auto _ : state) {
        std::uint32_t std = 0u;
        benchmark::DoNotOptimize(std);

        for (std::uint32_t i = 0u; i < UINT32_MAX; i++) {
            std *= std;
            std /= 2;
        }
    }
}

BENCHMARK(bm_std_test1);

static void bm_wrap_test1(benchmark::State& state) {
    for (auto _ : state) {
        u32 wrap = 0u;
        benchmark::DoNotOptimize(wrap);

        for (u32 i = 0u; i < u32::MAX; i++) {
            wrap *= wrap;
            wrap /= 2;
        }
    }
}

BENCHMARK(bm_wrap_test1);

static void bm_std_test2(benchmark::State& state) {
    for (auto _ : state) {
        float std = 0.f;
        benchmark::DoNotOptimize(std);
        
        for (std::int32_t i = 0; i < INT32_MAX; i++) {
            std *= std;
            std /= 2.f;
        }
    }
}

BENCHMARK(bm_std_test2);

static void bm_wrap_test2(benchmark::State& state) {
    for (auto _ : state) {
        f32 wrap = 0.f;
        benchmark::DoNotOptimize(wrap);

        for (i32 i = 0; i < i32::MAX; i++) {
            wrap *= wrap;
            wrap /= 2.f;
        }
    }
}

BENCHMARK(bm_wrap_test2);

BENCHMARK_MAIN();

#endif