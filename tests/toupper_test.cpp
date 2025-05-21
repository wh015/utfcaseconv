#include <catch2/catch.hpp>

#include <utf32caseconv/utf32caseconv.h>

TEST_CASE("Latin") {
    REQUIRE(utf32caseconv::toupper('a') == 'A');
    REQUIRE(utf32caseconv::toupper('Z') == 'Z');
}

TEST_CASE("Cyrillic") {
    REQUIRE(utf32caseconv::toupper(U'у') == U'У');
    REQUIRE(utf32caseconv::toupper(U'Д') == U'Д');
}
