#pragma once

#ifndef _UTFCASECONV_UTF8_H_
#define _UTFCASECONV_UTF8_H_

// Should be on the top.
// See: https://travisdowns.github.io/blog/2019/11/19/toupper.html
#include <utfcaseconv/utf32.h>
#include <utfcaseconv/utf8_constants.h>

#include <iterator>
#include <string>

// Such kind of UTF-8 conversion is based on
// https://github.com/BobSteagall/utf_utils.git
// Suitable of x86-64 or any other LE architecture.

namespace utfcaseconv {

template <typename IT>
inline size_t codepoint_32to8(char32_t cdpt, IT& dst) noexcept {
    if (cdpt < BORDER_ASCII)
    {
        *dst++ = static_cast<char>(cdpt);
        return 1;
    } else if (cdpt < BORDER_2BYTE)
    {
        *dst++ = static_cast<char>(0xC0 | ((cdpt >> 6) & 0x1F));
        *dst++ = static_cast<char>(0x80 | (cdpt & 0x3F));
        return 2;
    } else if (cdpt < BORDER_3BYTE)
    {
        *dst++ = static_cast<char>(0xE0 | ((cdpt >> 12) & 0x0F));
        *dst++ = static_cast<char>(0x80 | ((cdpt >> 6) & 0x3F));
        *dst++ = static_cast<char>(0x80 | (cdpt & 0x3F));
        return 3;
    } else if (cdpt < BORDER_4BYTE)
    {
        *dst++ = static_cast<char>(0xF0 | ((cdpt >> 18) & 0x07));
        *dst++ = static_cast<char>(0x80 | ((cdpt >> 12) & 0x3F));
        *dst++ = static_cast<char>(0x80 | ((cdpt >> 6) & 0x3F));
        *dst++ = static_cast<char>(0x80 | (cdpt & 0x3F));
        return 4;
    }
    return 0;
}

template <typename IT>
inline char32_t codepoint_8to32(IT& begin, IT end) noexcept {
    auto octet = static_cast<uint8_t>(*begin++);
    auto state = STATE_TABLE[octet];
    char32_t cdpt = OCTET_TABLE[octet];

    while (state > ERR)
    {
        if (begin == end)
        {
            return CODEPOINT32_INVALID;
        }

        octet = static_cast<uint8_t>(*begin++);
        const auto type = TYPE_TABLE[octet];
        cdpt = (cdpt << 6) | (octet & 0x3F);

        const auto lookup_index =
            static_cast<uint8_t>(state) + static_cast<uint8_t>(type);
        state = STATE_LOOKUP_TABLE[lookup_index];
    }

    return cdpt;
}

template <typename IT, typename IT2>
size_t toupper(IT begin, IT end, IT2 dst) noexcept {
    auto res = 0;
    while (begin != end)
    {
        auto octet = static_cast<uint8_t>(*begin);
        if (octet < BORDER_ASCII)
        {
            *dst++ = (octet < 'a' || octet > 'z') ? octet : octet - ASCII_CASEFOLDING_OFFSET;
            ++res;
            ++begin;
        } else
        {
            auto cdpt = codepoint_8to32(begin, end);
            if (cdpt == CODEPOINT32_INVALID)
            {
                break;
            }
            res += codepoint_32to8(utf32::toupper(cdpt), dst);
        }
    }
    return res;
}

template <typename IT, typename IT2>
size_t tolower(IT begin, IT end, IT2 dst) noexcept {
    auto res = 0;
    while (begin != end)
    {
        auto octet = static_cast<uint8_t>(*begin);
        if (octet < BORDER_ASCII)
        {
            *dst++ = (octet < 'A' || octet > 'Z') ? octet : octet + ASCII_CASEFOLDING_OFFSET;
            ++res;
            ++begin;
        } else
        {
            auto cdpt = codepoint_8to32(begin, end);
            if (cdpt == CODEPOINT32_INVALID)
            {
                break;
            }
            res += codepoint_32to8(utf32::tolower(cdpt), dst);
        }
    }
    return res;
}

template <typename T>
inline T toupper(const T& in) {
    T out;

    out.resize(in.size());
    auto sz = toupper(in.begin(), in.end(), out.begin());
    out.resize(sz);

    return out;
}

template <typename T>
inline T tolower(const T& in) {
    T out;

    out.resize(in.size());
    auto sz = tolower(in.begin(), in.end(), out.begin());
    out.resize(sz);

    return out;
}

inline std::string toupper(const std::string_view in) {
    std::string out;

    out.resize(in.size());
    auto sz = toupper(in.begin(), in.end(), out.begin());
    out.resize(sz);

    return out;
}

inline std::string tolower(const std::string_view in) {
    std::string out;

    out.resize(in.size());
    auto sz = tolower(in.begin(), in.end(), out.begin());
    out.resize(sz);

    return out;
}

} // namespace utfcaseconv

#endif
