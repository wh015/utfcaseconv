#include <stdexcept>
#include <string>

#include <benchmark/benchmark.h>

#include <unicode/uchar.h>
#include <unicode/ucasemap.h>

#include "benchmark_testing_data.h"

static constexpr std::string_view ascii = TESTING_DATA_ASCII;
static constexpr std::string_view cyrillic = TESTING_DATA_CYRILLIC;
static constexpr std::string_view mixed = TESTING_DATA_MIXED;

static UCaseMap* csm = nullptr;

template <typename ConvertionFunction>
static std::string change_case(const ConvertionFunction& converter,
                               std::string_view src) {
    UErrorCode err = U_ZERO_ERROR;

    std::string dst(src.size(), char{}); // +1 for terminating null

    assert(src.size() < std::numeric_limits<std::int32_t>::max());
    assert(dst.size() < std::numeric_limits<std::int32_t>::max());

    auto size =
        converter(csm, dst.data(), static_cast<std::int32_t>(dst.size()),
                  src.data(), static_cast<std::int32_t>(src.size()), &err);

    if (err == U_BUFFER_OVERFLOW_ERROR)
    {
        err = U_ZERO_ERROR;
        dst.resize(size);
        size =
            converter(csm, dst.data(), static_cast<std::int32_t>(dst.size()),
                      src.data(), static_cast<std::int32_t>(src.size()), &err);
    }

    if (U_FAILURE(err))
    {
        return std::string{};
    }

    return std::move(dst);
}

static auto toupper(std::string_view src) {
    return change_case(ucasemap_utf8ToUpper, src);
}

static auto tolower(std::string_view src) {
    return change_case(ucasemap_utf8ToLower, src);
}

static void MB_casemap_open(const benchmark::State& state) {
    UErrorCode err = U_ZERO_ERROR;

    csm = ucasemap_open(nullptr, U_FOLD_CASE_DEFAULT, &err);
    if (U_FAILURE(err))
    {
        throw std::runtime_error{"ucasemap_open failed, " +
                                 std::string{u_errorName(err)}};
    }
}

static void MB_casemap_close(const benchmark::State& state) {
    ucasemap_close(csm);
    csm = nullptr;
}

template <class... Args>
static void BM_icu_utf8_casemap_lower(benchmark::State& state, Args&&... args) {
    auto args_tuple = std::make_tuple(std::move(args)...);
    auto src = std::get<0>(args_tuple);

    for (auto _ : state)
    {
        tolower(src);
    }
}
BENCHMARK_CAPTURE(BM_icu_utf8_casemap_lower, ascii, ascii)
    ->Setup(MB_casemap_open)
    ->Teardown(MB_casemap_close);
BENCHMARK_CAPTURE(BM_icu_utf8_casemap_lower, cyrillic, cyrillic)
    ->Setup(MB_casemap_open)
    ->Teardown(MB_casemap_close);
BENCHMARK_CAPTURE(BM_icu_utf8_casemap_lower, mixed, mixed)
    ->Setup(MB_casemap_open)
    ->Teardown(MB_casemap_close);

template <class... Args>
static void BM_icu_utf8_casemap_upper(benchmark::State& state, Args&&... args) {
    auto args_tuple = std::make_tuple(std::move(args)...);
    auto src = std::get<0>(args_tuple);

    for (auto _ : state)
    {
        toupper(src);
    }
}
BENCHMARK_CAPTURE(BM_icu_utf8_casemap_upper, ascii, ascii)
    ->Setup(MB_casemap_open)
    ->Teardown(MB_casemap_close);
BENCHMARK_CAPTURE(BM_icu_utf8_casemap_upper, cyrillic, cyrillic)
    ->Setup(MB_casemap_open)
    ->Teardown(MB_casemap_close);
BENCHMARK_CAPTURE(BM_icu_utf8_casemap_upper, mixed, mixed)
    ->Setup(MB_casemap_open)
    ->Teardown(MB_casemap_close);

BENCHMARK_MAIN();
