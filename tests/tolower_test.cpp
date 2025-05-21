#include <catch2/catch.hpp>

#include <utf32caseconv/utf32caseconv.h>

TEST_CASE("Latin") {
    REQUIRE(utf32caseconv::tolower('L') == 'l');
    REQUIRE(utf32caseconv::tolower('x') == 'x');
}

TEST_CASE("Cyrillic") {
    REQUIRE(utf32caseconv::tolower(U'Ф') == U'ф');
    REQUIRE(utf32caseconv::tolower(U'ж') == U'ж');
}
