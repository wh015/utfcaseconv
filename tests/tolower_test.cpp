#include <catch2/catch_test_macros.hpp>

#include <string>
#include <cstring>

#include <utf32caseconv/utf32caseconv.h>

using namespace utf32caseconv;

TEST_CASE("Latin") {
    REQUIRE(tolower(U'A') == U'a');
    REQUIRE(tolower(U'Z') == U'z');
    REQUIRE(tolower(U'n') == U'n');
}

TEST_CASE("Cyrillic") {
    REQUIRE(tolower(U'А') == U'а');
    REQUIRE(tolower(U'Я') == U'я');
    REQUIRE(tolower(U'н') == U'н');
}

TEST_CASE("Greek") {
    REQUIRE(tolower(U'Α') == U'α');
    REQUIRE(tolower(U'Ω') == U'ω');
    REQUIRE(tolower(U'μ') == U'μ');
}

TEST_CASE("Coptic") {
    REQUIRE(tolower(U'Ⲁ') == U'ⲁ');
    REQUIRE(tolower(U'Ⳁ') == U'ⳁ');
    REQUIRE(tolower(U'ⲗ') == U'ⲗ');
}

TEST_CASE("Armenian") {
    REQUIRE(tolower(U'Ա') == U'ա');
    REQUIRE(tolower(U'Բ') == U'բ');
    REQUIRE(tolower(U'ճ') == U'ճ');
}

TEST_CASE("Glagolitic") {
    REQUIRE(tolower(U'Ⰰ') == U'ⰰ');
    REQUIRE(tolower(U'Ⱚ') == U'ⱚ');
    REQUIRE(tolower(U'ⱈ') == U'ⱈ');
}

TEST_CASE("Adlam") {
    REQUIRE(tolower(U'𞤀') == U'𞤢');
    REQUIRE(tolower(U'𞤛') == U'𞤽');
    REQUIRE(tolower(U'𞤯') == U'𞤯');
    // for loanwords
    REQUIRE(tolower(U'𞤊') == U'𞤬');
}

TEST_CASE("Warang Citi") {
    REQUIRE(tolower(U'𑢠') == U'𑣀');
    REQUIRE(tolower(U'𑢿') == U'𑣟');
    REQUIRE(tolower(U'𑣏') == U'𑣏');
}

TEST_CASE("Garay") {
    REQUIRE(tolower(U'𐵚') == U'𐵺');
    REQUIRE(tolower(U'𐵥') == U'𐶅');
    REQUIRE(tolower(U'𐶎') == U'𐶎');
}

TEST_CASE("Zaghawa") {
    // only proposed to be added to Unicode
}

TEST_CASE("Osage") {
    REQUIRE(tolower(U'𐒰') == U'𐓘');
    REQUIRE(tolower(U'𐓃') == U'𐓫');
    REQUIRE(tolower(U'𐓪') == U'𐓪');
}

TEST_CASE("Vithkuqi") {
    REQUIRE(tolower(U'𐕰') == U'𐖗');
    REQUIRE(tolower(U'𐖕') == U'𐖼');
    REQUIRE(tolower(U'𐖙') == U'𐖙');
}

TEST_CASE("Deseret") {
    REQUIRE(tolower(U'𐐀') == U'𐐨');
    REQUIRE(tolower(U'𐐧') == U'𐑏');
    REQUIRE(tolower(U'𐑅') == U'𐑅');
}

TEST_CASE("Georgian") {
    // asomtavruli & nuskhuri
    REQUIRE(tolower(U'Ⴀ') == U'ⴀ');
    REQUIRE(tolower(U'Ⴥ') == U'ⴥ');
    REQUIRE(tolower(U'ⴙ') == U'ⴙ');
    // mkhedruli & mtavruli
    REQUIRE(tolower(U'Ა') == U'ა');
    REQUIRE(tolower(U'Ჰ') == U'ჰ');
    REQUIRE(tolower(U'რ') == U'რ');
}

TEST_CASE("Non-bicameral") {
    REQUIRE(tolower(U'غ') == U'غ');
    REQUIRE(tolower(U'大') == U'大');
    REQUIRE(tolower(U'東') == U'東');
    REQUIRE(tolower(U'デ') == U'デ');
    REQUIRE(tolower(U'❤') == U'❤');
    REQUIRE(tolower(U'𐠔') == U'𐠔');
    REQUIRE(tolower(U'ᚦ') == U'ᚦ');
    REQUIRE(tolower(U'అ') == U'అ');
    REQUIRE(tolower(U'ㄱ') == U'ㄱ');
    REQUIRE(tolower(U'ஊ') == U'ஊ');
    REQUIRE(tolower(U'ฌ') == U'ฌ');
}

TEST_CASE("Strings") {
    std::u32string src = U"НеКаЯ СтРоКа";
    REQUIRE(tolower(src) == U"некая строка");
}

TEST_CASE("Arrays") {
    char32_t src[] = U"НеКаЯ СтРоКа";
    char32_t expected[] = U"некая строка";
    tolower_inplace(src, sizeof(src) / sizeof(*src));
    REQUIRE(memcmp(src, expected, sizeof(src)) == 0);
}
