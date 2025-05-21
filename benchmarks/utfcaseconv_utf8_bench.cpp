#include <string>

#include <benchmark/benchmark.h>

#include <utfcaseconv/utf8.h>

#include "benchmark_testing_data.h"

static constexpr std::string_view ascii = TESTING_DATA_ASCII;
static constexpr std::string_view cyrillic = TESTING_DATA_CYRILLIC;
static constexpr std::string_view mixed = TESTING_DATA_MIXED;

using namespace utfcaseconv;

template <class... Args>
static void BM_utfcaseconv_utf8_lower(benchmark::State& state, Args&&... args) {
    auto args_tuple = std::make_tuple(std::move(args)...);
    auto src = std::get<0>(args_tuple);

    for (auto _ : state)
    {
        tolower(src);
    }
}
BENCHMARK_CAPTURE(BM_utfcaseconv_utf8_lower, ascii, ascii);
BENCHMARK_CAPTURE(BM_utfcaseconv_utf8_lower, cyrillic, cyrillic);
BENCHMARK_CAPTURE(BM_utfcaseconv_utf8_lower, mixed, mixed);

template <class... Args>
static void BM_utfcaseconv_utf8_ascii_upper(benchmark::State& state,
                                            Args&&... args) {
    auto args_tuple = std::make_tuple(std::move(args)...);
    auto src = std::get<0>(args_tuple);

    for (auto _ : state)
    {
        toupper(src);
    }
}
BENCHMARK_CAPTURE(BM_utfcaseconv_utf8_ascii_upper, ascii, ascii);
BENCHMARK_CAPTURE(BM_utfcaseconv_utf8_ascii_upper, cyrillic, cyrillic);
BENCHMARK_CAPTURE(BM_utfcaseconv_utf8_ascii_upper, mixed, mixed);

BENCHMARK_MAIN();