#pragma once

#ifndef _UTFCASECONV_UTF32_H_
#define _UTFCASECONV_UTF32_H_

// Should be on the top.
// See: https://travisdowns.github.io/blog/2019/11/19/toupper.html
#include <ctype.h>

#include <type_traits>
#include <algorithm>

#include "utf32_tables.h"

namespace utfcaseconv {
namespace utf32 {

    template<size_t sz> char32_t convert(char32_t c, const std::array<char32_t, sz>& src,
        const std::array<char32_t, sz>& dst) {
        static_assert(sz > 0, "caseconv tables can not be empty");

        auto r = c;
        const auto it = std::lower_bound(src.begin(), src.end(), c);
        if(it != src.end()) {
            if(*it == c) {
                const auto offset = std::distance(src.begin(), it);
                r = *(dst.begin() + offset);
            }
        }
        return r;
    }

    static inline char32_t tolower(char32_t c) {
        return convert(c, upper_lower_src_tbl, upper_lower_dst_tbl);
    }

    static inline char32_t toupper(char32_t c) {
        return convert(c, lower_upper_src_tbl, lower_upper_dst_tbl);
    }

    template<typename IT, typename IT2> inline void tolower(IT begin, IT end, IT2 dst) {
        for(; begin != end; ++begin, ++dst) {
            *dst = tolower(*dst);
        }
    }

    template<typename IT, typename IT2> inline void toupper(IT begin, IT end, IT2 dst) {
        for(; begin != end; ++begin, ++dst) {
            *dst = toupper(*dst);
        }
    }

    template<typename IT> inline void tolower(IT begin, IT end) {
        for(; begin != end; ++begin) {
            *begin = tolower(*begin);
        }
    }

    template<typename IT> inline void toupper(IT begin, IT end) {
        for(; begin != end; ++begin) {
            *begin = toupper(*begin);
        }
    }

    template<typename T> inline T toupper(const T& in) {
        T out{in};
        toupper(in.begin(), in.end(), out.begin());
        return out;
    }

    template<typename T> inline T tolower(const T& in) {
        T out{in};
        tolower(in.begin(), in.end(), out.begin());
        return out;
    }
}
}

#endif
