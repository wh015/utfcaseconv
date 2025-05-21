#include <string>

#include <benchmark/benchmark.h>

#include <unicode/unistr.h>

#include "benchmark_testing_data.h"

static constexpr std::string_view ascii = TESTING_DATA_ASCII;
static constexpr std::string_view cyrillic = TESTING_DATA_CYRILLIC;
static constexpr std::string_view mixed = TESTING_DATA_MIXED;

using namespace icu;

template <class... Args>
static void BM_icu_utf8_lower(benchmark::State& state, Args&&... args) {
    auto args_tuple = std::make_tuple(std::move(args)...);
    auto src = std::get<0>(args_tuple);
    std::string dst;
    dst.reserve(src.size() + 1);

    for (auto _ : state) {
        UnicodeString tmp(src.data());
        tmp.toLower();
        tmp.toUTF8String(dst);
    }
}

BENCHMARK_CAPTURE(BM_icu_utf8_lower, ascii, ascii);
BENCHMARK_CAPTURE(BM_icu_utf8_lower, cyrillic, cyrillic);
BENCHMARK_CAPTURE(BM_icu_utf8_lower, mixed, mixed);

template <class... Args>
static void BM_icu_utf8_upper(benchmark::State& state, Args&&... args) {
    auto args_tuple = std::make_tuple(std::move(args)...);
    auto src = std::get<0>(args_tuple);
    std::string dst;
    dst.reserve(src.size() + 1);

    for (auto _ : state) {
        UnicodeString tmp(src.data());
        tmp.toUpper();
        tmp.toUTF8String(dst);
    }
}

BENCHMARK_CAPTURE(BM_icu_utf8_upper, ascii, ascii);
BENCHMARK_CAPTURE(BM_icu_utf8_upper, cyrillic, cyrillic);
BENCHMARK_CAPTURE(BM_icu_utf8_upper, mixed, mixed);

BENCHMARK_MAIN();
