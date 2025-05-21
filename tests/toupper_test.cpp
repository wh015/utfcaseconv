#include <catch2/catch.hpp>

#include <utf32caseconv/utf32caseconv.h>

using namespace utf32caseconv;

#include <catch2/catch.hpp>

#include <utf32caseconv/utf32caseconv.h>

using namespace utf32caseconv;

TEST_CASE("Latin") {
    REQUIRE(toupper(U'a') == U'A');
    REQUIRE(toupper(U'z') == U'Z');
    REQUIRE(toupper(U'N') == U'N');
}

TEST_CASE("Cyrillic") {
    REQUIRE(toupper(U'а') == U'А');
    REQUIRE(toupper(U'я') == U'Я');
    REQUIRE(toupper(U'Н') == U'Н');
}

TEST_CASE("Greek") {
    REQUIRE(toupper(U'α') == U'Α');
    REQUIRE(toupper(U'ω') == U'Ω');
    REQUIRE(toupper(U'Ψ') == U'Ψ');
}

TEST_CASE("Coptic") {
    REQUIRE(toupper(U'ⲁ') == U'Ⲁ');
    REQUIRE(toupper(U'ⳁ') == U'Ⳁ');
    REQUIRE(toupper(U'Ⲫ') == U'Ⲫ');
}

TEST_CASE("Armenian") {
    REQUIRE(toupper(U'ա') == U'Ա');
    REQUIRE(toupper(U'բ') == U'Բ');
    REQUIRE(toupper(U'Ձ') == U'Ձ');
}

TEST_CASE("Glagolitic") {
    REQUIRE(toupper(U'ⰰ') == U'Ⰰ');
    REQUIRE(toupper(U'ⱚ') == U'Ⱚ');
    REQUIRE(toupper(U'Ⱓ') == U'Ⱓ');
}

TEST_CASE("Adlam") {
    REQUIRE(toupper(U'𞤢') == U'𞤀');
    REQUIRE(toupper(U'𞤽') == U'𞤛');
    REQUIRE(toupper(U'𞤐') == U'𞤐');
    // for loanwords
    REQUIRE(toupper(U'𞤬') == U'𞤊');
}

TEST_CASE("Warang Citi") {
    REQUIRE(toupper(U'𑣀') == U'𑢠');
    REQUIRE(toupper(U'𑣟') == U'𑢿');
    REQUIRE(toupper(U'𑢫') == U'𑢫');
}

TEST_CASE("Garay") {
    REQUIRE(toupper(U'𐵺') == U'𐵚');
    REQUIRE(toupper(U'𐶅') == U'𐵥');
    REQUIRE(toupper(U'𐵕') == U'𐵕');
}

TEST_CASE("Zaghawa") {
    // only proposed to be added to Unicode
}

TEST_CASE("Osage") {
    REQUIRE(toupper(U'𐓘') == U'𐒰');
    REQUIRE(toupper(U'𐓫') == U'𐓃');
    REQUIRE(toupper(U'𐓋') == U'𐓋');
}

TEST_CASE("Vithkuqi") {
    REQUIRE(toupper(U'𐖗') == U'𐕰');
    REQUIRE(toupper(U'𐖼') == U'𐖕');
    REQUIRE(toupper(U'𐖄') == U'𐖄');
}

TEST_CASE("Deseret") {
    REQUIRE(toupper(U'𐐨') == U'𐐀');
    REQUIRE(toupper(U'𐑏') == U'𐐧');
    REQUIRE(toupper(U'𐐘') == U'𐐘');
}

TEST_CASE("Georgian") {
    // asomtavruli & nuskhuri
    REQUIRE(toupper(U'ⴀ') == U'Ⴀ');
    REQUIRE(toupper(U'ⴥ') == U'Ⴥ');
    REQUIRE(toupper(U'Ⴑ') == U'Ⴑ');
    // mkhedruli & mtavruli
    REQUIRE(toupper(U'ა') == U'Ა');
    REQUIRE(toupper(U'ჰ') == U'Ჰ');
    REQUIRE(toupper(U'Დ') == U'Დ');
}

TEST_CASE("Non-bicameral") {
    REQUIRE(toupper(U'غ') == U'غ');
    REQUIRE(toupper(U'大') == U'大');
    REQUIRE(toupper(U'東') == U'東');
    REQUIRE(toupper(U'デ') == U'デ');
    REQUIRE(toupper(U'❤') == U'❤');
    REQUIRE(toupper(U'𐠔') == U'𐠔');
    REQUIRE(toupper(U'ᚦ') == U'ᚦ');
    REQUIRE(toupper(U'అ') == U'అ');
    REQUIRE(toupper(U'ㄱ') == U'ㄱ');
    REQUIRE(toupper(U'ஊ') == U'ஊ');
    REQUIRE(toupper(U'ฌ') == U'ฌ');
}
