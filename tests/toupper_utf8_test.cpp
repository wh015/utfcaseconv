#include <string>
#include <cstring>
#include <vector>

#include <utfcaseconv/utf8.h>

#include <gtest/gtest.h>

using namespace utfcaseconv;

TEST(utf8_toupper_string, latin) {
    std::string s = "AnY StRiNg";
    ASSERT_EQ(toupper(s), "ANY STRING");
}

TEST(utf8_toupper_string, cyrillic) {
    std::string s = "НеКаЯ СтРоКа";
    ASSERT_EQ(toupper(s), "НЕКАЯ СТРОКА");
}

TEST(utf8_toupper_string, greek) {
    std::string s = "αωΨ";
    ASSERT_EQ(toupper(s), "ΑΩΨ");
}

TEST(utf8_toupper_string, coptic) {
    std::string s = "ⲁⳁⲪ";
    ASSERT_EQ(toupper(s), "ⲀⳀⲪ");
}

TEST(utf8_toupper_string, armenian) {
    std::string s = "աբՁ";
    ASSERT_EQ(toupper(s), "ԱԲՁ");
}

TEST(utf8_toupper_string, glagolitic) {
    std::string s = "ⰰⱚⰣ";
    ASSERT_EQ(toupper(s), "ⰀⰪⰣ");
}

TEST(utf8_toupper_string, adlam) {
    std::string s = "𞤢𞤽𞤐𞤬";
    ASSERT_EQ(toupper(s), "𞤀𞤛𞤐𞤊");
}

TEST(utf8_toupper_string, warang_citi) {
    std::string s = "𑣀𑣟𑢫";
    ASSERT_EQ(toupper(s), "𑢠𑢿𑢫");
}

TEST(utf8_toupper_string, garay) {
    std::string s = "𐵺𐵕𐶅";
    ASSERT_EQ(toupper(s), "𐵚𐵕𐵥");
}

TEST(utf8_toupper_string, zaghawa) {
    // only proposed to be added to Unicode
}

TEST(utf8_toupper_string, osage) {
    std::string s = "𐓘𐓫𐓋";
    ASSERT_EQ(toupper(s), "𐒰𐓃𐓋");
}

TEST(utf8_toupper_string, vithkuqi) {
    std::string s = "𐖗𐖼𐖄";
    ASSERT_EQ(toupper(s), "𐕰𐖕𐖄");
}

TEST(utf8_toupper_string, deseret) {
    std::string s = "𐐨𐑏𐐘";
    ASSERT_EQ(toupper(s), "𐐀𐐧𐐘");
}

TEST(utf8_toupper_string, georgian) {
    std::string s = "ⴀⴥႱაჰᲓ";
    ASSERT_EQ(toupper(s), "ႠჅႱᲐᲰᲓ");
}

TEST(utf8_toupper_string, mixed_long) {
    std::string s = "AnyStringКакая-тоСтрока1234567890Какая-тоСтрокаAnyString";
    ASSERT_EQ(toupper(s), "ANYSTRINGКАКАЯ-ТОСТРОКА1234567890КАКАЯ-ТОСТРОКАANYSTRING");
}

TEST(utf8_toupper_string, non_bicameral) {
    std::string s = "غ𐠔❤デ東大ᚦఅஊஊ";
    ASSERT_EQ(toupper(s), "غ𐠔❤デ東大ᚦఅஊஊ");
}

TEST(utf8_toupper_string_view, string_view) {
    std::string_view s = "НеКаЯ СтРоКа";
    ASSERT_EQ(toupper(s), "НЕКАЯ СТРОКА");
}

TEST(utf8_toupper_string_view, vector) {
    std::string_view s = "НеКаЯ СтРоКа";
    char expected[] = "НЕКАЯ СТРОКА";

    auto v = toupper<std::vector<char>>(s);
    ASSERT_EQ(memcmp(v.data(), expected, v.size()), 0);
}

TEST(utf8_toupper_array, array) {
    char src[] = "НеКаЯ СтРоКа";
    char expected[] = "НЕКАЯ СТРОКА";

    toupper(src, src + (sizeof(src) / sizeof(*src)), src);
    ASSERT_EQ(memcmp(src, expected, sizeof(src)), 0);
}
