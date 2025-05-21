#include <string>
#include <cstring>

#include <utfcaseconv/utf8.h>

#include "catch2_wrapper.h"

static constexpr char ascii[] = "ASCII";
static constexpr char cyrillic[] = "Кириллица";
static constexpr char mixed[] = "Miхеd";

using namespace utfcaseconv;

TEST_CASE("UTF-8 ASCII") {
    const char *src = ascii;
    size_t size = sizeof(ascii);
    char *dst = new char[size];

    BENCHMARK("ASCII to upper") {
        return toupper(src, src + size, dst);
    };

    BENCHMARK("ASCII to lower") {
        return toupper(src, src + size, dst);
    };

    delete dst;
}

TEST_CASE("UTF-8 Cyrllic") {
    const char *src = cyrillic;
    size_t size = sizeof(cyrillic);
    char *dst = new char[size];

    BENCHMARK("Cyrllic to upper") {
        return toupper(src, src + size, dst);
    };

    BENCHMARK("Cyrllic to lower") {
        return tolower(src, src + size, dst);
    };

    delete dst;
}

TEST_CASE("UTF-8 Mixed") {
    const char *src = mixed;
    size_t size = sizeof(mixed);
    char *dst = new char[size];

    BENCHMARK("Mixed to upper") {
        return toupper(src, src + size, dst);
    };

    BENCHMARK("Mixed to lower") {
        return tolower(src, src + size, dst);
    };

    delete dst;
}
