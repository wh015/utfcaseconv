#include <string>
#include <cstring>

#include <utfcaseconv/utf32.h>

#include <gtest/gtest.h>

using namespace utfcaseconv::utf32;

TEST(utf32_tolower_codepoint, latin) {
    ASSERT_EQ(tolower(U'A'), U'a');
    ASSERT_EQ(tolower(U'Z'), U'z');
    ASSERT_EQ(tolower(U'n'), U'n');
}

TEST(utf32_tolower_codepoint, cyrillic) {
    ASSERT_EQ(tolower(U'А'), U'а');
    ASSERT_EQ(tolower(U'Я'), U'я');
    ASSERT_EQ(tolower(U'н'), U'н');
}

TEST(utf32_tolower_codepoint, greek) {
    ASSERT_EQ(tolower(U'Α'), U'α');
    ASSERT_EQ(tolower(U'Ω'), U'ω');
    ASSERT_EQ(tolower(U'μ'), U'μ');
}

TEST(utf32_tolower_codepoint, coptic) {
    ASSERT_EQ(tolower(U'Ⲁ'), U'ⲁ');
    ASSERT_EQ(tolower(U'Ⳁ'), U'ⳁ');
    ASSERT_EQ(tolower(U'ⲗ'), U'ⲗ');
}

TEST(utf32_tolower_codepoint, armenian) {
    ASSERT_EQ(tolower(U'Ա'), U'ա');
    ASSERT_EQ(tolower(U'Բ'), U'բ');
    ASSERT_EQ(tolower(U'ճ'), U'ճ');
}

TEST(utf32_tolower_codepoint, glagolitic) {
    ASSERT_EQ(tolower(U'Ⰰ'), U'ⰰ');
    ASSERT_EQ(tolower(U'Ⱚ'), U'ⱚ');
    ASSERT_EQ(tolower(U'ⱈ'), U'ⱈ');
}

TEST(utf32_tolower_codepoint, adlam) {
    ASSERT_EQ(tolower(U'𞤀'), U'𞤢');
    ASSERT_EQ(tolower(U'𞤛'), U'𞤽');
    ASSERT_EQ(tolower(U'𞤯'), U'𞤯');
    // for loanwords
    ASSERT_EQ(tolower(U'𞤊'), U'𞤬');
}

TEST(utf32_tolower_codepoint, warang_citi) {
    ASSERT_EQ(tolower(U'𑢠'), U'𑣀');
    ASSERT_EQ(tolower(U'𑢿'), U'𑣟');
    ASSERT_EQ(tolower(U'𑣏'), U'𑣏');
}

TEST(utf32_tolower_codepoint, garay) {
    ASSERT_EQ(tolower(U'𐵚'), U'𐵺');
    ASSERT_EQ(tolower(U'𐵥'), U'𐶅');
    ASSERT_EQ(tolower(U'𐶎'), U'𐶎');
}

TEST(utf32_tolower_codepoint, zaghawa) {
    // only proposed to be added to Unicode
}

TEST(utf32_tolower_codepoint, osage) {
    ASSERT_EQ(tolower(U'𐒰'), U'𐓘');
    ASSERT_EQ(tolower(U'𐓃'), U'𐓫');
    ASSERT_EQ(tolower(U'𐓪'), U'𐓪');
}

TEST(utf32_tolower_codepoint, vithkuqi) {
    ASSERT_EQ(tolower(U'𐕰'), U'𐖗');
    ASSERT_EQ(tolower(U'𐖕'), U'𐖼');
    ASSERT_EQ(tolower(U'𐖙'), U'𐖙');
}

TEST(utf32_tolower_codepoint, deseret) {
    ASSERT_EQ(tolower(U'𐐀'), U'𐐨');
    ASSERT_EQ(tolower(U'𐐧'), U'𐑏');
    ASSERT_EQ(tolower(U'𐑅'), U'𐑅');
}

TEST(utf32_tolower_codepoint, georgian) {
    // asomtavruli & nuskhuri
    ASSERT_EQ(tolower(U'Ⴀ'), U'ⴀ');
    ASSERT_EQ(tolower(U'Ⴥ'), U'ⴥ');
    ASSERT_EQ(tolower(U'ⴙ'), U'ⴙ');
    // mkhedruli & mtavruli
    ASSERT_EQ(tolower(U'Ა'), U'ა');
    ASSERT_EQ(tolower(U'Ჰ'), U'ჰ');
    ASSERT_EQ(tolower(U'რ'), U'რ');
}

TEST(utf32_tolower_codepoint, non_bicameral) {
    ASSERT_EQ(tolower(U'غ'), U'غ');
    ASSERT_EQ(tolower(U'大'), U'大');
    ASSERT_EQ(tolower(U'東'), U'東');
    ASSERT_EQ(tolower(U'デ'), U'デ');
    ASSERT_EQ(tolower(U'❤'), U'❤');
    ASSERT_EQ(tolower(U'𐠔'), U'𐠔');
    ASSERT_EQ(tolower(U'ᚦ'), U'ᚦ');
    ASSERT_EQ(tolower(U'అ'), U'అ');
    ASSERT_EQ(tolower(U'ㄱ'), U'ㄱ');
    ASSERT_EQ(tolower(U'ஊ'), U'ஊ');
    ASSERT_EQ(tolower(U'ฌ'), U'ฌ');
}

TEST(utf32_tolower_sequence, string) {
    std::u32string src = U"НеКаЯ СтРоКа";
    ASSERT_EQ(tolower(src), U"некая строка");
}

TEST(utf32_tolower_sequence, array) {
    char32_t src[] = U"НеКаЯ СтРоКа";
    char32_t expected[] = U"некая строка";
    tolower(src, src + (sizeof(src) / sizeof(*src)));
    ASSERT_EQ(memcmp(src, expected, sizeof(src)), 0);
}
