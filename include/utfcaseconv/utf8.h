#pragma once

#ifndef _UTFCASECONV_UTF8_H_
#define _UTFCASECONV_UTF8_H_

// Should be on the top.
// See: https://travisdowns.github.io/blog/2019/11/19/toupper.html
#include <cctype>
#include <iterator>
#include <string>

#include <utfcaseconv/utf32.h>
#include <utfcaseconv/utf8_constants.h>
#include <utfcaseconv/platform.h>

// Such kind of UTF-8 conversion is based on
// https://github.com/BobSteagall/utf_utils.git
// Suitable of x86-64 or any other LE architecture.

namespace utfcaseconv {

template <typename IT>
inline void codepoint_32to8(char32_t cdpt, IT& dst) noexcept {
    if (cdpt < BORDER_ASCII) {
        *dst++ = static_cast<char>(cdpt);
    } else if (cdpt < BORDER_2BYTE) {
        *dst++ = static_cast<char>(0xC0 | ((cdpt >> 6) & 0x1F));
        *dst++ = static_cast<char>(0x80 | (cdpt & 0x3F));
    } else if (cdpt < BORDER_3BYTE) {
        *dst++ = static_cast<char>(0xE0 | ((cdpt >> 12) & 0x0F));
        *dst++ = static_cast<char>(0x80 | ((cdpt >> 6) & 0x3F));
        *dst++ = static_cast<char>(0x80 | (cdpt & 0x3F));
    } else if (cdpt < BORDER_4BYTE) {
        *dst++ = static_cast<char>(0xF0 | ((cdpt >> 18) & 0x07));
        *dst++ = static_cast<char>(0x80 | ((cdpt >> 12) & 0x3F));
        *dst++ = static_cast<char>(0x80 | ((cdpt >> 6) & 0x3F));
        *dst++ = static_cast<char>(0x80 | (cdpt & 0x3F));
    }
}

template <typename IT>
inline char32_t codepoint_8to32(IT& begin, IT end) noexcept {
    auto octet = static_cast<uint8_t>(*begin++);
    auto state = STATE_TABLE[octet];
    char32_t cdpt = OCTET_TABLE[octet];

    while (state > ERR) {
        if (begin == end) {
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
auto toupper(IT begin, IT end, IT2 dst) noexcept {
    static_assert(
        std::is_same<std::random_access_iterator_tag,
                     typename std::iterator_traits<IT>::iterator_category>::value,
        "toupper() accepts random access iterators only");
    static_assert(
        std::is_same<std::random_access_iterator_tag,
                     typename std::iterator_traits<IT2>::iterator_category>::value,
        "toupper() accepts random access iterators only");

    auto initial = begin;

    if constexpr (PLATFORM >= Platform::SSE) {
        constexpr typename std::iterator_traits<IT>::difference_type VECTOR_SIZE = 16;

        while (std::distance(begin, end) >= VECTOR_SIZE) {
            auto octet = static_cast<uint8_t>(*begin);
            if (octet < BORDER_ASCII) {
                toupper_sse(begin, dst);
            } else {
                auto cdpt = codepoint_8to32(begin, end);
                if (cdpt == CODEPOINT32_INVALID) {
                    break;
                }
                codepoint_32to8(utf32::toupper(cdpt), dst);
            }
        }
    }

    while (begin != end) {
        auto octet = static_cast<uint8_t>(*begin);
        if (octet < BORDER_ASCII) {
            *dst++ =
                (octet < 'a' || octet > 'z') ? octet : octet - ASCII_CASEFOLDING_OFFSET;
            ++begin;
        } else {
            auto cdpt = codepoint_8to32(begin, end);
            if (cdpt == CODEPOINT32_INVALID) {
                break;
            }
            codepoint_32to8(utf32::toupper(cdpt), dst);
        }
    }

    return std::distance(initial, begin);
}

template <typename IT, typename IT2>
auto tolower(IT begin, IT end, IT2 dst) noexcept {
    static_assert(
        std::is_same<std::random_access_iterator_tag,
                     typename std::iterator_traits<IT>::iterator_category>::value,
        "tolower() accepts random access iterators only");
    static_assert(
        std::is_same<std::random_access_iterator_tag,
                     typename std::iterator_traits<IT2>::iterator_category>::value,
        "tolower() accepts random access iterators only");

    auto initial = begin;

    if constexpr (PLATFORM >= Platform::SSE) {
        constexpr typename std::iterator_traits<IT>::difference_type VECTOR_SIZE = 16;

        while (std::distance(begin, end) >= VECTOR_SIZE) {
            auto octet = static_cast<uint8_t>(*begin);
            if (octet < BORDER_ASCII) {
                tolower_sse(begin, dst);
            } else {
                auto cdpt = codepoint_8to32(begin, end);
                if (cdpt == CODEPOINT32_INVALID) {
                    break;
                }
                codepoint_32to8(utf32::tolower(cdpt), dst);
            }
        }
    }

    while (begin != end) {
        auto octet = static_cast<uint8_t>(*begin);
        if (octet < BORDER_ASCII) {
            *dst++ =
                (octet < 'A' || octet > 'Z') ? octet : octet + ASCII_CASEFOLDING_OFFSET;
            ++begin;
        } else {
            auto cdpt = codepoint_8to32(begin, end);
            if (cdpt == CODEPOINT32_INVALID) {
                break;
            }
            codepoint_32to8(utf32::tolower(cdpt), dst);
        }
    }

    return std::distance(initial, begin);
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

template <typename T = std::string>
inline T toupper(const std::string_view in) {
    T out;

    out.resize(in.size());
    auto sz = toupper(in.begin(), in.end(), out.begin());
    out.resize(sz);

    return out;
}

template <typename T = std::string>
inline T tolower(const std::string_view in) {
    T out;

    out.resize(in.size());
    auto sz = tolower(in.begin(), in.end(), out.begin());
    out.resize(sz);

    return out;
}

} // namespace utfcaseconv

#endif
