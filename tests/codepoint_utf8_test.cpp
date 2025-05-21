#include <string>
#include <cstring>
#include <array>

#include <utfcaseconv/utf8.h>

#include <gtest/gtest.h>

using namespace utfcaseconv;

TEST(utf8_to_utf32_codepoint, simple) {
    std::string s = "AпⳀ❤";
    std::array expected = {U'A', U'п', U'Ⳁ', U'❤'};

    auto it = s.begin();
    for (size_t i = 0; i < expected.size(); ++i) {
        auto res = codepoint_8to32(it, s.end());
        ASSERT_EQ(res, expected[i]);
    }
}
