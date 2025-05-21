find_package(GTest REQUIRED)

include(CTest)

add_executable(toupper_utf32_test toupper_utf32_test.cpp)
target_link_libraries(toupper_utf32_test PRIVATE utfcaseconv GTest::gtest GTest::gtest_main)
add_test(NAME "toupper-utf32-test" COMMAND toupper_utf32_test)

add_executable(tolower_utf32_test tolower_utf32_test.cpp)
target_link_libraries(tolower_utf32_test PRIVATE utfcaseconv GTest::gtest GTest::gtest_main)
add_test(NAME "tolower-utf32-test" COMMAND tolower_utf32_test)

add_executable(codepoint_utf8_test codepoint_utf8_test.cpp)
target_link_libraries(codepoint_utf8_test PRIVATE utfcaseconv GTest::gtest GTest::gtest_main)
add_test(NAME "codepoint-utf8-test" COMMAND codepoint_utf8_test)

add_executable(toupper_utf8_test toupper_utf8_test.cpp)
target_link_libraries(toupper_utf8_test PRIVATE utfcaseconv GTest::gtest GTest::gtest_main)
add_test(NAME "toupper-utf8-test" COMMAND toupper_utf8_test)

add_executable(tolower_utf8_test tolower_utf8_test.cpp)
target_link_libraries(tolower_utf8_test PRIVATE utfcaseconv GTest::gtest GTest::gtest_main)
add_test(NAME "tolower-utf8-test" COMMAND tolower_utf8_test)

if(WITH_LINUX_INTRINSICS)
    add_executable(toupper_utf8_sse_test toupper_utf8_test.cpp)
    target_link_libraries(toupper_utf8_sse_test PRIVATE utfcaseconv GTest::gtest GTest::gtest_main)
    target_compile_options(toupper_utf8_sse_test PRIVATE -msse4.2)
    add_test(NAME "toupper-utf8-sse-test" COMMAND toupper_utf8_sse_test)

    add_executable(tolower_utf8_sse_test tolower_utf8_test.cpp)
    target_link_libraries(tolower_utf8_sse_test PRIVATE utfcaseconv GTest::gtest GTest::gtest_main)
    target_compile_options(tolower_utf8_sse_test PRIVATE -msse4.2)
    add_test(NAME "tolower-utf8-sse-test" COMMAND tolower_utf8_sse_test)
endif()
