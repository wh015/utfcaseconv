#pragma once

#ifndef _UTF32_CASECONV_H_
#define _UTF32_CASECONV_H_

#include <algorithm>

#include "utf32caseconv_tables.h"

namespace utf32caseconv {
    static char32_t tolower(char32_t c) {
        auto r = c;
        const auto it = std::lower_bound(upper_lower_src_tbl.begin(), upper_lower_src_tbl.end(), c);
        if(it != upper_lower_src_tbl.end()) {
            if(*it == c) {
                const auto offset = std::distance(upper_lower_src_tbl.begin(), it);
                r = *(upper_lower_dst_tbl.begin() + offset);
            }
        }
        return r;
    }

    static char32_t toupper(char32_t c) {
        auto r = c;
        const auto it = std::lower_bound(lower_upper_src_tbl.begin(), lower_upper_src_tbl.end(), c);
        if(it != lower_upper_src_tbl.end()) {
            if(*it == c) {
                const auto offset = std::distance(lower_upper_src_tbl.begin(), it);
                r = *(lower_upper_dst_tbl.begin() + offset);
            }
        }
        return r;
    }
}

#endif
