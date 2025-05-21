
find_package(Catch2 CONFIG REQUIRED)

include(CTest)
include(Catch)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(toupper_test toupper_test.cpp)
target_link_libraries(toupper_test PRIVATE utf32caseconv Catch2::Catch2WithMain)
add_test(NAME "toupper-test" COMMAND toupper_test)

add_executable(tolower_test tolower_test.cpp)
target_link_libraries(tolower_test PRIVATE utf32caseconv Catch2::Catch2WithMain)
add_test(NAME "tolower-test" COMMAND tolower_test)
