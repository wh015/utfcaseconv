#include <string>
#include <cstring>

#include <utfcaseconv/utf32.h>

#include "catch2_wrapper.h"

static constexpr char32_t ascii[] = U"ASCII";
static constexpr char32_t cyrillic[] = U"Кириллица";
static constexpr char32_t mixed[] = U"Miхеd";

using namespace utfcaseconv::utf32;

TEST_CASE("UTF-32 ASCII") {
    const char32_t *src = ascii;
    size_t size = sizeof(ascii);
    char32_t *dst = new char32_t[size];

    BENCHMARK("ASCII to upper") {
        return toupper(src, src + size, dst);
    };

    BENCHMARK("ASCII to lower") {
        return toupper(src, src + size, dst);
    };

    delete dst;
}

TEST_CASE("UTF-32 Cyrllic") {
    const char32_t *src = cyrillic;
    size_t size = sizeof(cyrillic);
    char32_t *dst = new char32_t[size];

    BENCHMARK("Cyrllic to upper") {
        return toupper(src, src + size, dst);
    };

    BENCHMARK("Cyrllic to lower") {
        return tolower(src, src + size, dst);
    };

    delete dst;
}

TEST_CASE("UTF-32 Mixed") {
    const char32_t *src = mixed;
    size_t size = sizeof(mixed);
    char32_t *dst = new char32_t[size];

    BENCHMARK("Mixed to upper") {
        return toupper(src, src + size, dst);
    };

    BENCHMARK("Mixed to lower") {
        return tolower(src, src + size, dst);
    };

    delete dst;
}
