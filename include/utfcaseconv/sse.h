#pragma once

#ifndef _UTFCASECONV_SSE_H_
#define _UTFCASECONV_SSE_H_

namespace utfcaseconv {

template <typename IT, typename IT2>
inline void tolower_sse(IT& from, IT2& to) noexcept {
    const char* pfrom = &(*from);
    char* pto = &(*to);

    auto src = _mm_loadu_si128((const __m128i*)pfrom);

    auto ga = _mm_cmpgt_epi8(src, _mm_set1_epi8('A' - 1));
    auto lz = _mm_cmpgt_epi8(_mm_set1_epi8('Z' + 1), src);

    auto alpla = _mm_and_si128(ga, lz);

    auto v0 = _mm_and_si128(alpla, _mm_set1_epi8(0x20));
    auto v1 = _mm_xor_si128(src, v0);
    _mm_storeu_si128((__m128i*)pto, v1);

    auto mask = _mm_movemask_epi8(src);
    auto count = (mask == 0) ? sizeof(__m128i) : ctz(mask);

    from += count;
    to += count;
}

template <typename IT, typename IT2>
inline void toupper_sse(IT& from, IT2& to) noexcept {
    const char* pfrom = &(*from);
    char* pto = &(*to);

    auto src = _mm_loadu_si128((const __m128i*)pfrom);

    auto ga = _mm_cmpgt_epi8(src, _mm_set1_epi8('a' - 1));
    auto lz = _mm_cmpgt_epi8(_mm_set1_epi8('z' + 1), src);

    auto alpla = _mm_and_si128(ga, lz);

    auto v0 = _mm_and_si128(alpla, _mm_set1_epi8(0x20));
    auto v1 = _mm_xor_si128(src, v0);
    _mm_storeu_si128((__m128i*)pto, v1);

    auto mask = _mm_movemask_epi8(src);
    auto count = (mask == 0) ? sizeof(__m128i) : ctz(mask);

    from += count;
    to += count;
}

} // namespace utfcaseconv

#endif
