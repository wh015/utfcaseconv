
find_package(Catch2 CONFIG REQUIRED)

include(CTest)
include(Catch)

add_executable(toupper_utf32_test toupper_utf32_test.cpp)
target_link_libraries(toupper_utf32_test PRIVATE utfcaseconv Catch2::Catch2WithMain)
add_test(NAME "toupper-utf32-test" COMMAND toupper_utf32_test)

add_executable(tolower_utf32_test tolower_utf32_test.cpp)
target_link_libraries(tolower_utf32_test PRIVATE utfcaseconv Catch2::Catch2WithMain)
add_test(NAME "tolower-utf32-test" COMMAND tolower_utf32_test)
