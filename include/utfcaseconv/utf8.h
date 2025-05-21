#pragma once

#ifndef _UTFCASECONV_UTF8_H_
#define _UTFCASECONV_UTF8_H_

// Should be on the top.
// See: https://travisdowns.github.io/blog/2019/11/19/toupper.html
#include <utfcaseconv/utf32.h>
#include <utfcaseconv/utf8_constants.h>

#include <iterator>
#include <string>

#include <immintrin.h>

// Such kind of UTF-8 conversion is based on
// https://github.com/BobSteagall/utf_utils.git
// Suitable of x86-64 or any other LE architecture.

namespace utfcaseconv {

static inline unsigned int ctz(unsigned int v)
{
#ifdef WIN32
    return _tzcnt_u32(v);
#else
    return __builtin_ctz(v);
#endif
}

template <typename IT>
inline size_t codepoint_32to8(char32_t cdpt, IT& dst) noexcept {
    if (cdpt < BORDER_ASCII) {
        *dst++ = static_cast<char>(cdpt);
        return 1;
    } else if (cdpt < BORDER_2BYTE) {
        *dst++ = static_cast<char>(0xC0 | ((cdpt >> 6) & 0x1F));
        *dst++ = static_cast<char>(0x80 | (cdpt & 0x3F));
        return 2;
    } else if (cdpt < BORDER_3BYTE) {
        *dst++ = static_cast<char>(0xE0 | ((cdpt >> 12) & 0x0F));
        *dst++ = static_cast<char>(0x80 | ((cdpt >> 6) & 0x3F));
        *dst++ = static_cast<char>(0x80 | (cdpt & 0x3F));
        return 3;
    } else if (cdpt < BORDER_4BYTE) {
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
inline size_t tolower_sse(IT& from, IT2& to) {
    const char *pfrom = &(*from);
    char *pto = &(*to);

    auto src = _mm_loadu_si128((const __m128i*)pfrom);

    auto ga = _mm_cmpgt_epi8(src, _mm_set1_epi8('A' - 1));
    auto lz = _mm_cmpgt_epi8(_mm_set1_epi8('Z' + 1), src);

    auto alpla = _mm_and_si128(ga, lz);

    auto v0 = _mm_and_si128(alpla, _mm_set1_epi8(0x20));
    auto v1 = _mm_xor_si128(src, v0);
    _mm_storeu_si128((__m128i*)&(*to), v1);

    auto mask = _mm_movemask_epi8(src);
    auto count = (mask == 0) ? sizeof(__m128i) : ctz(mask);

    from += count;
    to += count;

    return count;
}

template <typename IT, typename IT2>
inline size_t toupper_sse(IT& from, IT2& to) {
    const char *pfrom = &(*from);
    char *pto = &(*to);

    auto src = _mm_loadu_si128((const __m128i*)pfrom);

    auto ga = _mm_cmpgt_epi8(src, _mm_set1_epi8('a' - 1));
    auto lz = _mm_cmpgt_epi8(_mm_set1_epi8('z' + 1), src);

    auto alpla = _mm_and_si128(ga, lz);

    auto v0 = _mm_and_si128(alpla, _mm_set1_epi8(0x20));
    auto v1 = _mm_xor_si128(src, v0);
    _mm_storeu_si128((__m128i*)&(*to), v1);

    auto mask = _mm_movemask_epi8(src);
    auto count = (mask == 0) ? sizeof(__m128i) : ctz(mask);

    from += count;
    to += count;

    return count;
}


template <typename IT, typename IT2>
size_t toupper(IT begin, IT end, IT2 dst) noexcept {
    auto res = 0;

    while (std::distance(begin, end) >= sizeof(__m128i)) {
        auto octet = static_cast<uint8_t>(*begin);
        if (octet < BORDER_ASCII) {
            res += toupper_sse(begin, dst);
        } else {
            auto cdpt = codepoint_8to32(begin, end);
            if (cdpt == CODEPOINT32_INVALID) {
                break;
            }
            res += codepoint_32to8(utf32::toupper(cdpt), dst);
        }
    }

    while (begin != end) {
        auto octet = static_cast<uint8_t>(*begin);
        if (octet < BORDER_ASCII) {
            *dst++ =
                (octet < 'a' || octet > 'z') ? octet : octet - ASCII_CASEFOLDING_OFFSET;
            ++res;
            ++begin;
        } else {
            auto cdpt = codepoint_8to32(begin, end);
            if (cdpt == CODEPOINT32_INVALID) {
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

    while (std::distance(begin, end) >= sizeof(__m128i)) {
        auto octet = static_cast<uint8_t>(*begin);
        if (octet < BORDER_ASCII) {
            res += tolower_sse(begin, dst);
        } else {
            auto cdpt = codepoint_8to32(begin, end);
            if (cdpt == CODEPOINT32_INVALID) {
                break;
            }
            res += codepoint_32to8(utf32::tolower(cdpt), dst);
        }
    }

    while (begin != end) {
        auto octet = static_cast<uint8_t>(*begin);
        if (octet < BORDER_ASCII) {
            *dst++ =
                (octet < 'A' || octet > 'Z') ? octet : octet + ASCII_CASEFOLDING_OFFSET;
            ++res;
            ++begin;
        } else {
            auto cdpt = codepoint_8to32(begin, end);
            if (cdpt == CODEPOINT32_INVALID) {
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
