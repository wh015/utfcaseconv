#pragma once

#ifndef _UTFCASECONV_PLATFORM_H_
#define _UTFCASECONV_PLATFORM_H_

#include <cstdint>

// Windows doesn't have predefined macro for SSE
// so, let's assume we just have it on x86_64
#define UTFCASECONV_MSVC_X86_64                                                          \
    (defined(WIN32) && defined(_M_AMD64) && !defined(_M_ARM64) && !defined(_M_ARM64EC))

#define UTFCASECONV_PLATFORM_GEN (0)
#define UTFCASECONV_PLATFORM_SSE (1 << 0)

namespace utfcaseconv {
enum Platform : uint8_t {
    GEN = UTFCASECONV_PLATFORM_GEN,
    SSE = UTFCASECONV_PLATFORM_SSE,
};

#if UTFCASECONV_MSVC_X86_64 || defined(__SSE4_2__)
#define UTFCASECONV_PLATFORM UTFCASECONV_PLATFORM_SSE
static constexpr Platform PLATFORM = Platform::SSE;
#else
#define UTFCASECONV_PLATFORM UTFCASECONV_PLATFORM_GEN
static constexpr Platform PLATFORM = Platform::GEN;
#endif
} // namespace utfcaseconv

#define UTFCASECONV_INTRINSICS (UTFCASECONV_PLATFORM >= UTFCASECONV_PLATFORM_SSE)

#if (UTFCASECONV_INTRINSICS)
#include <immintrin.h>

namespace utfcaseconv {

static inline unsigned int ctz(unsigned int v) {
#ifdef WIN32
    return _tzcnt_u32(v);
#else
    return __builtin_ctz(v);
#endif
}

} // namespace utfcaseconv
#endif

#if (UTFCASECONV_PLATFORM >= UTFCASECONV_PLATFORM_SSE)
#include <utfcaseconv/sse.h>
#endif

#endif
