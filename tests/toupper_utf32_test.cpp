#include <string>
#include <cstring>

#include <utfcaseconv/utf32.h>

#include <gtest/gtest.h>

using namespace utfcaseconv::utf32;

TEST(utf32_toupper_codepoint, latin) {
    ASSERT_EQ(toupper(U'a'), U'A');
    ASSERT_EQ(toupper(U'z'), U'Z');
    ASSERT_EQ(toupper(U'N'), U'N');
}

TEST(utf32_toupper_codepoint, cyrillic) {
    ASSERT_EQ(toupper(U'а'), U'А');
    ASSERT_EQ(toupper(U'я'), U'Я');
    ASSERT_EQ(toupper(U'Н'), U'Н');
}

TEST(utf32_toupper_codepoint, greek) {
    ASSERT_EQ(toupper(U'α'), U'Α');
    ASSERT_EQ(toupper(U'ω'), U'Ω');
    ASSERT_EQ(toupper(U'Ψ'), U'Ψ');
}

TEST(utf32_toupper_codepoint, coptic) {
    ASSERT_EQ(toupper(U'ⲁ'), U'Ⲁ');
    ASSERT_EQ(toupper(U'ⳁ'), U'Ⳁ');
    ASSERT_EQ(toupper(U'Ⲫ'), U'Ⲫ');
}

TEST(utf32_toupper_codepoint, armenian) {
    ASSERT_EQ(toupper(U'ա'), U'Ա');
    ASSERT_EQ(toupper(U'բ'), U'Բ');
    ASSERT_EQ(toupper(U'Ձ'), U'Ձ');
}

TEST(utf32_toupper_codepoint, glagolitic) {
    ASSERT_EQ(toupper(U'ⰰ'), U'Ⰰ');
    ASSERT_EQ(toupper(U'ⱚ'), U'Ⱚ');
    ASSERT_EQ(toupper(U'Ⱓ'), U'Ⱓ');
}

TEST(utf32_toupper_codepoint, adlam) {
    ASSERT_EQ(toupper(U'𞤢'), U'𞤀');
    ASSERT_EQ(toupper(U'𞤽'), U'𞤛');
    ASSERT_EQ(toupper(U'𞤐'), U'𞤐');
    // for loanwords
    ASSERT_EQ(toupper(U'𞤬'), U'𞤊');
}

TEST(utf32_toupper_codepoint, warang_citi) {
    ASSERT_EQ(toupper(U'𑣀'), U'𑢠');
    ASSERT_EQ(toupper(U'𑣟'), U'𑢿');
    ASSERT_EQ(toupper(U'𑢫'), U'𑢫');
}

TEST(utf32_toupper_codepoint, garay) {
    ASSERT_EQ(toupper(U'𐵺'), U'𐵚');
    ASSERT_EQ(toupper(U'𐶅'), U'𐵥');
    ASSERT_EQ(toupper(U'𐵕'), U'𐵕');
}

TEST(utf32_toupper_codepoint, zaghawa) {
    // only proposed to be added to Unicode
}

TEST(utf32_toupper_codepoint, osage) {
    ASSERT_EQ(toupper(U'𐓘'), U'𐒰');
    ASSERT_EQ(toupper(U'𐓫'), U'𐓃');
    ASSERT_EQ(toupper(U'𐓋'), U'𐓋');
}

TEST(utf32_toupper_codepoint, vithkuqi) {
    ASSERT_EQ(toupper(U'𐖗'), U'𐕰');
    ASSERT_EQ(toupper(U'𐖼'), U'𐖕');
    ASSERT_EQ(toupper(U'𐖄'), U'𐖄');
}

TEST(utf32_toupper_codepoint, deseret) {
    ASSERT_EQ(toupper(U'𐐨'), U'𐐀');
    ASSERT_EQ(toupper(U'𐑏'), U'𐐧');
    ASSERT_EQ(toupper(U'𐐘'), U'𐐘');
}

TEST(utf32_toupper_codepoint, georgian) {
    // asomtavruli & nuskhuri
    ASSERT_EQ(toupper(U'ⴀ'), U'Ⴀ');
    ASSERT_EQ(toupper(U'ⴥ'), U'Ⴥ');
    ASSERT_EQ(toupper(U'Ⴑ'), U'Ⴑ');
    // mkhedruli & mtavruli
    ASSERT_EQ(toupper(U'ა'), U'Ა');
    ASSERT_EQ(toupper(U'ჰ'), U'Ჰ');
    ASSERT_EQ(toupper(U'Დ'), U'Დ');
}

TEST(utf32_toupper_codepoint, non_bicameral) {
    ASSERT_EQ(toupper(U'غ'), U'غ');
    ASSERT_EQ(toupper(U'大'), U'大');
    ASSERT_EQ(toupper(U'東'), U'東');
    ASSERT_EQ(toupper(U'デ'), U'デ');
    ASSERT_EQ(toupper(U'❤'), U'❤');
    ASSERT_EQ(toupper(U'𐠔'), U'𐠔');
    ASSERT_EQ(toupper(U'ᚦ'), U'ᚦ');
    ASSERT_EQ(toupper(U'అ'), U'అ');
    ASSERT_EQ(toupper(U'ㄱ'), U'ㄱ');
    ASSERT_EQ(toupper(U'ஊ'), U'ஊ');
    ASSERT_EQ(toupper(U'ฌ'), U'ฌ');
}

TEST(utf32_toupper_string32, string) {
    std::u32string src = U"НеКаЯ СтРоКа";
    ASSERT_EQ(toupper(src), U"НЕКАЯ СТРОКА");
}

TEST(utf32_toupper_string32, mixed_long) {
    std::u32string src = U"AnyStringКакая-тоСтрока1234567890Какая-тоСтрокаAnyString";
    ASSERT_EQ(toupper(src), U"ANYSTRINGКАКАЯ-ТОСТРОКА1234567890КАКАЯ-ТОСТРОКАANYSTRING");
}

TEST(utf32_toupper_array, array) {
    char32_t src[] = U"НеКаЯ СтРоКа";
    char32_t expected[] = U"НЕКАЯ СТРОКА";

    toupper(src, src + (sizeof(src) / sizeof(*src)), src);
    ASSERT_EQ(memcmp(src, expected, sizeof(src)), 0);
}
