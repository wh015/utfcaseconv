#include <string>

#include <benchmark/benchmark.h>

#include <utfcaseconv/utf32.h>

#include "benchmark_testing_data.h"

static constexpr std::u32string_view ascii = U"" TESTING_DATA_ASCII;
static constexpr std::u32string_view cyrillic = U"" TESTING_DATA_CYRILLIC;
static constexpr std::u32string_view mixed = U"" TESTING_DATA_MIXED;

using namespace utfcaseconv::utf32;

template <class... Args>
static void BM_utfcaseconv_utf32_lower(benchmark::State& state, Args&&... args) {
    auto args_tuple = std::make_tuple(std::move(args)...);
    auto src = std::get<0>(args_tuple);

    for (auto _ : state) {
        tolower(src);
    }
}

BENCHMARK_CAPTURE(BM_utfcaseconv_utf32_lower, ascii, ascii);
BENCHMARK_CAPTURE(BM_utfcaseconv_utf32_lower, cyrillic, cyrillic);
BENCHMARK_CAPTURE(BM_utfcaseconv_utf32_lower, mixed, mixed);

template <class... Args>
static void BM_utfcaseconv_utf32_upper(benchmark::State& state, Args&&... args) {
    auto args_tuple = std::make_tuple(std::move(args)...);
    auto src = std::get<0>(args_tuple);

    for (auto _ : state) {
        toupper(src);
    }
}

BENCHMARK_CAPTURE(BM_utfcaseconv_utf32_upper, ascii, ascii);
BENCHMARK_CAPTURE(BM_utfcaseconv_utf32_upper, cyrillic, cyrillic);
BENCHMARK_CAPTURE(BM_utfcaseconv_utf32_upper, mixed, mixed);

BENCHMARK_MAIN();
