find_package(Catch2 CONFIG REQUIRED)

include(CTest)
include(Catch)

if(MSVC)
    add_compile_options(/DCATCH2_VERSION=${Catch2_VERSION_MAJOR})
else()
    add_compile_options(-DCATCH2_VERSION=${Catch2_VERSION_MAJOR})
endif()

add_executable(utf32_bench utf32_bench.cpp)
target_link_libraries(utf32_bench PRIVATE utfcaseconv Catch2::Catch2WithMain)
add_test(NAME "utf32-bench" COMMAND utf32_bench)

add_executable(utf8_bench utf8_bench.cpp)
target_link_libraries(utf8_bench PRIVATE utfcaseconv Catch2::Catch2WithMain)
add_test(NAME "utf8-bench" COMMAND utf8_bench)
