#pragma once

#ifndef _UTFCASECONV_UTF32_H_
#define _UTFCASECONV_UTF32_H_

// Should be on the top.
// See: https://travisdowns.github.io/blog/2019/11/19/toupper.html
#include <ctype.h>

#include <iterator>
#include <type_traits>
#include <algorithm>

#include <utfcaseconv/utf32_tables.h>

namespace utfcaseconv {
namespace utf32 {

// faster binary search
// https://mhdm.dev/posts/sb_lower_bound/
template <class ForwardIt, class T>
constexpr ForwardIt sb_lower_bound(ForwardIt first, ForwardIt last, const T value) {
   auto length = last - first;
   while (length > 0) {
      auto half = length / 2;
      if (first[half] < value) {
         // length - half equals half + length % 2
         first += length - half;
      }
      length = half;
   }
   return first;
}

template <size_t sz>
char32_t convert(char32_t c, const std::array<char32_t, sz>& src,
                 const std::array<char32_t, sz>& dst) noexcept {
    static_assert(sz > 0, "caseconv tables can not be empty");

    auto r = c;
    const auto it = sb_lower_bound(src.begin(), src.end(), c);
    if (it != src.end())
    {
        if (*it == c)
        {
            const auto offset = std::distance(src.begin(), it);
            r = *(dst.begin() + offset);
        }
    }
    return r;
}

static inline char32_t tolower(char32_t c) noexcept {
    return convert(c, upper_lower_src_tbl, upper_lower_dst_tbl);
}

static inline char32_t toupper(char32_t c) noexcept {
    return convert(c, lower_upper_src_tbl, lower_upper_dst_tbl);
}

template <typename IT, typename IT2>
inline size_t tolower(IT begin, IT end, IT2 dst) noexcept {
    size_t res = 0;
    while (begin != end)
    {
        *dst++ = tolower(*begin++);
        ++res;
    }
    return res;
}

template <typename IT, typename IT2>
inline size_t toupper(IT begin, IT end, IT2 dst) noexcept {
    size_t res = 0;
    while (begin != end)
    {
        *dst++ = toupper(*begin++);
        ++res;
    }
    return res;
}

template <typename IT>
inline size_t tolower(IT begin, IT end) noexcept {
    size_t res = 0;
    while (begin != end)
    {
        *begin = tolower(*begin);
        ++begin;
        ++res;
    }
    return res;
}

template <typename IT>
inline size_t toupper(IT begin, IT end) noexcept {
    size_t res = 0;
    while (begin != end)
    {
        *begin = toupper(*begin);
        ++begin;
        ++res;
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

inline std::u32string toupper(std::u32string_view in) {
    std::u32string out;
    out.reserve(in.size());
    toupper(in.begin(), in.end(), std::back_inserter(out));
    return out;
}

inline std::u32string tolower(std::u32string_view in) {
    std::u32string out;
    out.reserve(in.size());
    tolower(in.begin(), in.end(), std::back_inserter(out));
    return out;
}

} // namespace utf32
} // namespace utfcaseconv

#endif
