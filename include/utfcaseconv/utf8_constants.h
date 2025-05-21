#pragma once

#ifndef _UTFCASECONV_UTF8_CONSTANTS_H_
#define _UTFCASECONV_UTF8_CONSTANTS_H_

#include <cstdint>
#include <array>

namespace utfcaseconv {

enum State : uint8_t {
    BGN = 0,   // Begin
    ERR = 12,  // Invalid sequence
    CS1 = 24,  // Continuation state 1
    CS2 = 36,  // Continuation state 2
    CS3 = 48,  // Continuation state 3
    P3A = 60,  // Partial 3-byte sequence state A
    P3B = 72,  // Partial 3-byte sequence state B
    P4A = 84,  // Partial 4-byte sequence state A
    P4B = 96,  // Partial 4-byte sequence state B
    END = BGN, // Begin and end are the same state
};

enum Type : uint8_t {
    ILL = 0,  // C0..C1, F5..FF  ILLEGAL octets that should never appear in a
              // UTF-8 sequence
    ASC = 1,  // 00..7F          ASCII leading byte range
    CR1 = 2,  // 80..8F          Continuation range 1
    CR2 = 3,  // 90..9F          Continuation range 2
    CR3 = 4,  // A0..BF          Continuation range 3
    L2A = 5,  // C2..DF          Leading byte range A / 2-byte sequence
    L3A = 6,  // E0              Leading byte range A / 3-byte sequence
    L3B = 7,  // E1..EC, EE..EF  Leading byte range B / 3-byte sequence
    L3C = 8,  // ED              Leading byte range C / 3-byte sequence
    L4A = 9,  // F0              Leading byte range A / 4-byte sequence
    L4B = 10, // F1..F3          Leading byte range B / 4-byte sequence
    L4C = 11, // F4              Leading byte range C / 4-byte sequence
};

static constexpr char32_t CODEPOINT32_INVALID = 0xFFFFFFFF;

enum Border : char32_t {
    BORDER_ASCII = 0x80,
    BORDER_2BYTE = 0x800,
    BORDER_3BYTE = 0x10000,
    BORDER_4BYTE = 0x110000,
};

// clang-format off
static constexpr std::array<uint8_t, 256> OCTET_TABLE = {{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, // 00..0F
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, // 10..1F
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, // 20..2F
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, // 30..3F

    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, // 40..4F
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, // 50..5F
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, // 60..6F
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, // 70..7F

    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, // 80..8F
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, // 90..9F
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, // A0..AF
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, // B0..BF

    0xC0, 0xC1, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, // C0..CF
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, // D0..DF
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, // E0..EF
    0x00, 0x01, 0x02, 0x03, 0x04, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF, // F0..FF
}};

static constexpr std::array<State, 256> STATE_TABLE = {{
    BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, // 00..0F
    BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, // 10..1F
    BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, // 20..2F
    BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, // 30..3F

    BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, // 40..4F
    BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, // 50..5F
    BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, // 60..6F
    BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, BGN, // 70..7F

    ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, // 80..8F
    ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, // 90..9F
    ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, // A0..AF
    ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, // B0..BF

    ERR, ERR, CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, // C0..CF
    CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, CS1, // D0..DF
    P3A, CS2, CS2, CS2, CS2, CS2, CS2, CS2, CS2, CS2, CS2, CS2, CS2, P3B, CS2, CS2, // E0..EF
    P4A, CS3, CS3, CS3, P4B, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, // F0..FF
}};

static constexpr std::array<Type, 256> TYPE_TABLE = {{
    ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, // 00..0F
    ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, // 10..1F
    ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, // 20..2F
    ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, // 30..3F

    ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, // 40..4F
    ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, // 50..5F
    ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, // 60..6F
    ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, ASC, // 70..7F

    CR1, CR1, CR1, CR1, CR1, CR1, CR1, CR1, CR1, CR1, CR1, CR1, CR1, CR1, CR1, CR1, // 80..8F
    CR2, CR2, CR2, CR2, CR2, CR2, CR2, CR2, CR2, CR2, CR2, CR2, CR2, CR2, CR2, CR2, // 90..9F
    CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, // A0..AF
    CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, CR3, // B0..BF

    ILL, ILL, L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, // C0..CF
    L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, L2A, // D0..DF
    L3A, L3B, L3B, L3B, L3B, L3B, L3B, L3B, L3B, L3B, L3B, L3B, L3B, L3C, L3B, L3B, // E0..EF
    L4A, L4B, L4B, L4B, L4C, ILL, ILL, ILL, ILL, ILL, ILL, ILL, ILL, ILL, ILL, ILL, // F0..FF
}};

static constexpr std::array<State, 108> STATE_LOOKUP_TABLE = {{
    /*
    ILL  ASC  CR1  CR2  CR3  L2A  L3A  L3B  L3C  L4A  L4B  L4C
    */
    ERR, END, ERR, ERR, ERR, CS1, P3A, CS2, P3B, P4A, CS3, P4B, // BGN | END
    ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, // ERR

    ERR, ERR, END, END, END, ERR, ERR, ERR, ERR, ERR, ERR, ERR, // CS1
    ERR, ERR, CS1, CS1, CS1, ERR, ERR, ERR, ERR, ERR, ERR, ERR, // CS2
    ERR, ERR, CS2, CS2, CS2, ERR, ERR, ERR, ERR, ERR, ERR, ERR, // CS3

    ERR, ERR, ERR, ERR, CS1, ERR, ERR, ERR, ERR, ERR, ERR, ERR, // P3A
    ERR, ERR, CS1, CS1, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, // P3B

    ERR, ERR, ERR, CS2, CS2, ERR, ERR, ERR, ERR, ERR, ERR, ERR, // P4A
    ERR, ERR, CS2, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, // P4B
}};
// clang-format on

} // namespace utfcaseconv

#endif
