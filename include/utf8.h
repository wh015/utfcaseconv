#pragma once

#ifndef _UTFCASECONV_UTF8_H_
#define _UTFCASECONV_UTF8_H_

// Should be on the top.
// See: https://travisdowns.github.io/blog/2019/11/19/toupper.html
#include "utf32.h"
#include "utf8_constants.h"

#include <iterator>
#include <string>

// Such kind of UTF-8 conversion is based on
// https://github.com/BobSteagall/utf_utils.git
// Suitable of x86-64 or any other LE architecture.


namespace utfcaseconv {

template <typename IT>
size_t codepoint_32to8(char32_t cdpt, IT& dst) {
    if (cdpt <= 0x7F)
    {
        *dst++ = (char)(cdpt);
        return 1;
    } else if (cdpt <= 0x7FF)
    {
        *dst++ = (char)(0xC0 | ((cdpt >> 6) & 0x1F));
        *dst++ = (char)(0x80 | (cdpt & 0x3F));
        return 2;
    } else if (cdpt <= 0xFFFF)
    {
        *dst++ = (char)(0xE0 | ((cdpt >> 12) & 0x0F));
        *dst++ = (char)(0x80 | ((cdpt >> 6) & 0x3F));
        *dst++ = (char)(0x80 | (cdpt & 0x3F));
        return 3;
    } else if (cdpt <= 0x10FFFF)
    {
        *dst++ = (char)(0xF0 | ((cdpt >> 18) & 0x07));
        *dst++ = (char)(0x80 | ((cdpt >> 12) & 0x3F));
        *dst++ = (char)(0x80 | ((cdpt >> 6) & 0x3F));
        *dst++ = (char)(0x80 | (cdpt & 0x3F));
        return 4;
    }
    return 0;
}

template <typename IT>
inline char32_t codepoint_8to32(IT& begin, IT end) noexcept {
    auto octet = static_cast<uint8_t>(*begin++);
    auto state = stateTable[octet];
    char32_t cdpt = octetTable[octet];

    while (state > ERR)
    {
        if (begin == end)
        {
            return CodePoint32Invalid;
        }

        octet = static_cast<uint8_t>(*begin++);
        auto type = typeTable[octet];
        cdpt = (cdpt << 6) | (octet & 0x3F);
        state = stateLookupTable[state + type];
    }

    return cdpt;
}

template <typename IT, typename IT2>
inline size_t toupper(IT begin, IT end, IT2 dst) {
    auto res = 0;
    while (begin != end)
    {
        auto cdpt = codepoint_8to32(begin, end);
        if (cdpt == CodePoint32Invalid)
        {
            break;
        }
        res += codepoint_32to8(utf32::toupper(cdpt), dst);
    }
    return res;
}

template <typename IT, typename IT2>
inline size_t tolower(IT begin, IT end, IT2 dst) {
    auto res = 0;
    while (begin != end)
    {
        auto cdpt = codepoint_8to32(begin, end);
        if (cdpt == CodePoint32Invalid)
        {
            break;
        }
        res += codepoint_32to8(utf32::tolower(cdpt), dst);
    }
    return res;
}

template <typename T>
inline T toupper(const T& in) {
    T out;
    out.reserve(in.size());
    toupper(in.begin(), in.end(), std::back_inserter(out));
    return out;
}

template <typename T>
inline T tolower(const T& in) {
    T out;
    out.reserve(in.size());
    tolower(in.begin(), in.end(), std::back_inserter(out));
    return out;
}

inline std::string toupper(const std::string_view in) {
    std::string out;
    out.reserve(in.size());
    toupper(in.begin(), in.end(), std::back_inserter(out));
    return out;
}

inline std::string tolower(const std::string_view in) {
    std::string out;
    out.reserve(in.size());
    tolower(in.begin(), in.end(), std::back_inserter(out));
    return out;
}

} // namespace utfcaseconv

#endif
