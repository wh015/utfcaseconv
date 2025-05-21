find_package(Catch2 CONFIG REQUIRED)

include(CTest)
include(Catch)

if(MSVC)
    add_compile_options(/DCATCH2_VERSION=${Catch2_VERSION_MAJOR})
else()
    add_compile_options(-DCATCH2_VERSION=${Catch2_VERSION_MAJOR})
endif()

add_executable(toupper_utf32_test toupper_utf32_test.cpp)
target_link_libraries(toupper_utf32_test PRIVATE utfcaseconv Catch2::Catch2WithMain)
add_test(NAME "toupper-utf32-test" COMMAND toupper_utf32_test)

add_executable(tolower_utf32_test tolower_utf32_test.cpp)
target_link_libraries(tolower_utf32_test PRIVATE utfcaseconv Catch2::Catch2WithMain)
add_test(NAME "tolower-utf32-test" COMMAND tolower_utf32_test)

add_executable(codepoint_utf8_test codepoint_utf8_test.cpp)
target_link_libraries(codepoint_utf8_test PRIVATE utfcaseconv Catch2::Catch2WithMain)
add_test(NAME "codepoint-utf8-test" COMMAND codepoint_utf8_test)

add_executable(toupper_utf8_test toupper_utf8_test.cpp)
target_link_libraries(toupper_utf8_test PRIVATE utfcaseconv Catch2::Catch2WithMain)
add_test(NAME "toupper-utf8-test" COMMAND toupper_utf8_test)

add_executable(tolower_utf8_test tolower_utf8_test.cpp)
target_link_libraries(tolower_utf8_test PRIVATE utfcaseconv Catch2::Catch2WithMain)
add_test(NAME "tolower-utf8-test" COMMAND tolower_utf8_test)
