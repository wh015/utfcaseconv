#pragma once

#ifndef _UTF32_CASECONV_H_
#define _UTF32_CASECONV_H_

// See: https://travisdowns.github.io/blog/2019/11/19/toupper.html
#include <ctype.h>

#include <type_traits>
#include <algorithm>

#include "utf32caseconv_tables.h"

namespace utf32caseconv {

    template<size_t sz> char32_t convert(char32_t c, const std::array<char32_t, sz>& src,
        const std::array<char32_t, sz>& dst) {
        static_assert(sz > 0, "utf32caseconv tables can not be empty");

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

    template<typename IT> inline void tolower_inplace(IT begin, IT end) {
        for(auto it = begin; it != end; it = std::next(it)) {
            *it = tolower(*it);
        }
    }

    template<typename IT> inline void toupper_inplace(IT begin, IT end) {
        for(auto it = begin; it != end; it = std::next(it)) {
            *it = toupper(*it);
        }
    }

    static inline void tolower_inplace(char32_t* in, size_t sz) {
        tolower_inplace(in, in + sz);
    }

    static inline void toupper_inplace(char32_t* in, size_t sz) {
        toupper_inplace(in, in + sz);
    }

    template<typename T> inline void tolower_inplace(T& in) {
        tolower_inplace(in.begin(), in.end());
    }

    template<typename T> inline void toupper_inplace(T& in) {
        toupper_inplace(in.begin(), in.end());
    }

    template<typename T> inline T toupper(const T& in) {
        T out{in};
        toupper_inplace(out);
        return out;
    }

    template<typename T> inline T tolower(const T& in) {
        T out{in};
        tolower_inplace(out);
        return out;
    }
}

#endif
