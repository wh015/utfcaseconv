#include <string>
#include <cstring>
#include <vector>

#include <utfcaseconv/utf8.h>

#include <gtest/gtest.h>

using namespace utfcaseconv;

TEST(utf8_tolower_string, Latin) {
    std::string s = "AnY StRiNg";
    ASSERT_EQ(tolower(s), "any string");
}

TEST(utf8_tolower_string, cyrillic) {
    std::string s = "НеКаЯ СтРоКа";
    ASSERT_EQ(tolower(s), "некая строка");
}

TEST(utf8_tolower_string, greek) {
    std::string s = "ΑΩμ";
    ASSERT_EQ(tolower(s), "αωμ");
}

TEST(utf8_tolower_string, coptic) {
    std::string s = "ⲀⳀⲗ";
    ASSERT_EQ(tolower(s), "ⲁⳁⲗ");
}

TEST(utf8_tolower_string, armenian) {
    std::string s = "ԱԲճ";
    ASSERT_EQ(tolower(s), "աբճ");
}

TEST(utf8_tolower_string, glagolitic) {
    std::string s = "ⰀⰪⱈ";
    ASSERT_EQ(tolower(s), "ⰰⱚⱈ");
}

TEST(utf8_tolower_string, adlam) {
    std::string s = "𞤀𞤛𞤯𞤊";
    ASSERT_EQ(tolower(s), "𞤢𞤽𞤯𞤬");
}

TEST(utf8_tolower_string, warang_citi) {
    std::string s = "𑢠𑢿𑣏";
    ASSERT_EQ(tolower(s), "𑣀𑣟𑣏");
}

TEST(utf8_tolower_string, garay) {
    std::string s = "𐵚𐵥𐶎";
    ASSERT_EQ(tolower(s), "𐵺𐶅𐶎");
}

TEST(utf8_tolower_string, zaghawa) {
    // only proposed to be added to Unicode
}

TEST(utf8_tolower_string, osage) {
    std::string s = "𐒰𐓃𐓪";
    ASSERT_EQ(tolower(s), "𐓘𐓫𐓪");
}

TEST(utf8_tolower_string, vithkuqi) {
    std::string s = "𐕰𐖕𐖙";
    ASSERT_EQ(tolower(s), "𐖗𐖼𐖙");
}

TEST(utf8_tolower_string, deseret) {
    std::string s = "𐐀𐐧𐑅";
    ASSERT_EQ(tolower(s), "𐐨𐑏𐑅");
}

TEST(utf8_tolower_string, georgian) {
    std::string s = "ႠჅⴙᲐᲰრ";
    ASSERT_EQ(tolower(s), "ⴀⴥⴙაჰრ");
}

TEST(utf8_lower_string, mixed_long) {
    std::string s = "AnyStringКакая-тоСтрока1234567890Какая-тоСтрокаAnyString";
    ASSERT_EQ(tolower(s), "anystringкакая-тострока1234567890какая-тострокаanystring");
}

TEST(utf8_tolower_string, non_bicameral) {
    std::string s = "غ𐠔❤デ東大ᚦఅஊஊ";
    ASSERT_EQ(tolower(s), "غ𐠔❤デ東大ᚦఅஊஊ");
}

TEST(utf8_tolower_string_view, string_view) {
    std::string_view s = "НеКаЯ СтРоКа";
    ASSERT_EQ(tolower(s), "некая строка");
}

TEST(utf8_tolower_string_view, vector) {
    std::string_view s = "НеКаЯ СтРоКа";
    char expected[] = "некая строка";

    auto v = tolower<std::vector<char>>(s);
    ASSERT_EQ(memcmp(v.data(), expected, v.size()), 0);
}

TEST(utf8_tolower_array, array) {
    char src[] = "НеКаЯ СтРоКа";
    char expected[] = "некая строка";

    tolower(src, src + (sizeof(src) / sizeof(*src)), src);
    ASSERT_EQ(memcmp(src, expected, sizeof(src)), 0);
}
