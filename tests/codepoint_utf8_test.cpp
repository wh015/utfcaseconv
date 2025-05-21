#include <catch2/catch_test_macros.hpp>

#include <string>
#include <cstring>

#include <utfcaseconv/utf8.h>

using namespace utfcaseconv;

TEST_CASE("UTF-8 to UTF-32 codepoints") {
    std::string s = "AпⳀ❤";
    char32_t expected[] = {U'A', U'п', U'Ⳁ', U'❤'};

    auto it = s.begin();
    for (size_t i = 0; i < sizeof(expected) / sizeof(*expected); ++i)
    {
        auto res = codepoint_8to32(it, s.end());
        REQUIRE(res == expected[i]);
    }
}
