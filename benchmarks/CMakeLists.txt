find_package(benchmark REQUIRED)

if(WITH_BENCHMARKS_ICU)
    find_package(ICU COMPONENTS uc i18n)
endif()

include(CTest)

add_executable(utfcaseconv_utf32_bench utfcaseconv_utf32_bench.cpp)
target_link_libraries(utfcaseconv_utf32_bench PRIVATE utfcaseconv benchmark::benchmark)
add_test(NAME "utfcaseconv-utf32-bench" COMMAND utfcaseconv_utf32_bench)

add_executable(utfcaseconv_utf8_bench utfcaseconv_utf8_bench.cpp)
target_link_libraries(utfcaseconv_utf8_bench PRIVATE utfcaseconv benchmark::benchmark)
add_test(NAME "utfcaseconv-utf8-bench" COMMAND utfcaseconv_utf8_bench)

if(WITH_BENCHMARKS_ICU)
    add_executable(icu_utf8_bench icu_utf8_bench.cpp)
    target_link_libraries(icu_utf8_bench PRIVATE ICU::uc ICU::i18n benchmark::benchmark)
    add_test(NAME "icu-utf8-bench" COMMAND icu_utf8_bench)

    add_executable(icu_utf8_casemap_bench icu_utf8_casemap_bench.cpp)
    target_link_libraries(icu_utf8_casemap_bench PRIVATE ICU::uc ICU::i18n benchmark::benchmark)
    add_test(NAME "icu-utf8-casemap-bench" COMMAND icu_utf8_casemap_bench)
endif()
