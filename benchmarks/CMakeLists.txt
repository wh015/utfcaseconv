find_package(benchmark REQUIRED)

include(CTest)

add_executable(utf32_bench utf32_bench.cpp)
target_link_libraries(utf32_bench PRIVATE utfcaseconv benchmark::benchmark)
add_test(NAME "utf32-bench" COMMAND utf32_bench)

add_executable(utf8_bench utf8_bench.cpp)
target_link_libraries(utf8_bench PRIVATE utfcaseconv benchmark::benchmark)
add_test(NAME "utf8-bench" COMMAND utf8_bench)
