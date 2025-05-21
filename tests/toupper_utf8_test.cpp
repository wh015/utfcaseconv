#include <string>
#include <cstring>

#include <utfcaseconv/utf8.h>

#include "catch2_wrapper.h"

using namespace utfcaseconv;

TEST_CASE("Latin") {
    std::string s = "PoSiTiVe";
    REQUIRE(toupper(s) == "POSITIVE");
}

TEST_CASE("Cyrillic") {
    std::string s = "ПоЗиТиВ";
    REQUIRE(toupper(s) == "ПОЗИТИВ");
}

TEST_CASE("Greek") {
    std::string s = "αωΨ";
    REQUIRE(toupper(s) == "ΑΩΨ");
}

TEST_CASE("Coptic") {
    std::string s = "ⲁⳁⲪ";
    REQUIRE(toupper(s) == "ⲀⳀⲪ");
}

TEST_CASE("Armenian") {
    std::string s = "աբՁ";
    REQUIRE(toupper(s) == "ԱԲՁ");
}

TEST_CASE("Glagolitic") {
    std::string s = "ⰰⱚⰣ";
    REQUIRE(toupper(s) == "ⰀⰪⰣ");
}

TEST_CASE("Adlam") {
    std::string s = "𞤢𞤽𞤐𞤬";
    REQUIRE(toupper(s) == "𞤀𞤛𞤐𞤊");
}

TEST_CASE("Warang Citi") {
    std::string s = "𑣀𑣟𑢫";
    REQUIRE(toupper(s) == "𑢠𑢿𑢫");
}

TEST_CASE("Garay") {
    std::string s = "𐵺𐵕𐶅";
    REQUIRE(toupper(s) == "𐵚𐵕𐵥");
}

TEST_CASE("Zaghawa") {
    // only proposed to be added to Unicode
}

TEST_CASE("Osage") {
    std::string s = "𐓘𐓫𐓋";
    REQUIRE(toupper(s) == "𐒰𐓃𐓋");
}

TEST_CASE("Vithkuqi") {
    std::string s = "𐖗𐖼𐖄";
    REQUIRE(toupper(s) == "𐕰𐖕𐖄");
}

TEST_CASE("Deseret") {
    std::string s = "𐐨𐑏𐐘";
    REQUIRE(toupper(s) == "𐐀𐐧𐐘");
}

TEST_CASE("Georgian") {
    std::string s = "ⴀⴥႱაჰᲓ";
    REQUIRE(toupper(s) == "ႠჅႱᲐᲰᲓ");
}

TEST_CASE("Non-bicameral") {
    std::string s = "غ𐠔❤デ東大ᚦఅஊஊ";
    REQUIRE(toupper(s) == "غ𐠔❤デ東大ᚦఅஊஊ");
}

TEST_CASE("Arrays") {
    char src[] = "ПоЗиТиВ";
    char expected[] = "ПОЗИТИВ";

    toupper(src, src + (sizeof(src) / sizeof(*src)), src);
    REQUIRE(memcmp(src, expected, sizeof(src)) == 0);
}
