#include <catch2/catch_test_macros.hpp>

#include <string>
#include <cstring>

#include <utfcaseconv/utf8.h>

using namespace utfcaseconv;

TEST_CASE("Latin") {
    std::string s = "PoSiTivE";
    REQUIRE(tolower(s) == "positive");
}

TEST_CASE("Cyrillic") {
    std::string s = "ПоЗиТив";
    REQUIRE(tolower(s) == "позитив");
}

TEST_CASE("Greek") {
    std::string s = "ΑΩμ";
    REQUIRE(tolower(s) == "αωμ");
}

TEST_CASE("Coptic") {
    std::string s = "ⲀⳀⲗ";
    REQUIRE(tolower(s) == "ⲁⳁⲗ");
}

TEST_CASE("Armenian") {
    std::string s = "ԱԲճ";
    REQUIRE(tolower(s) == "աբճ");
}

TEST_CASE("Glagolitic") {
    std::string s = "ⰀⰪⱈ";
    REQUIRE(tolower(s) == "ⰰⱚⱈ");
}

TEST_CASE("Adlam") {
    std::string s = "𞤀𞤛𞤯𞤊";
    REQUIRE(tolower(s) == "𞤢𞤽𞤯𞤬");
}

TEST_CASE("Warang Citi") {
    std::string s = "𑢠𑢿𑣏";
    REQUIRE(tolower(s) == "𑣀𑣟𑣏");
}

TEST_CASE("Garay") {
    std::string s = "𐵚𐵥𐶎";
    REQUIRE(tolower(s) == "𐵺𐶅𐶎");
}

TEST_CASE("Zaghawa") {
    // only proposed to be added to Unicode
}

TEST_CASE("Osage") {
    std::string s = "𐒰𐓃𐓪";
    REQUIRE(tolower(s) == "𐓘𐓫𐓪");
}

TEST_CASE("Vithkuqi") {
    std::string s = "𐕰𐖕𐖙";
    REQUIRE(tolower(s) == "𐖗𐖼𐖙");
}

TEST_CASE("Deseret") {
    std::string s = "𐐀𐐧𐑅";
    REQUIRE(tolower(s) == "𐐨𐑏𐑅");
}

TEST_CASE("Georgian") {
    std::string s = "ႠჅⴙᲐᲰრ";
    REQUIRE(tolower(s) == "ⴀⴥⴙაჰრ");
}

TEST_CASE("Non-bicameral") {
    std::string s = "غ𐠔❤デ東大ᚦఅஊஊ";
    REQUIRE(tolower(s) == "غ𐠔❤デ東大ᚦఅஊஊ");
}

TEST_CASE("Arrays") {
    char src[] = "ПоЗиТиВ";
    char expected[] = "позитив";

    tolower(src, src + (sizeof(src) / sizeof(*src)), src);
    REQUIRE(memcmp(src, expected, sizeof(src)) == 0);
}
