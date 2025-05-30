#!/usr/bin/python3

import argparse
import sys

class CaseconvItem:
    def __init__(self, upper, lower, desc):
        self.upper = upper
        self.lower = lower
        self.desc = desc


def open_r(path):
    if(path == None):
        return sys.stdin
    return open(path, 'r')

def open_w(path):
    if(path == None):
        return sys.stdout
    return open(path, 'w')


def array_begin(name, sz):
    return f"static constexpr std::array<char32_t, {sz}> {name}{{{{\n"

def array_value(val, desc):
    return f"    0x{val:08X}, // {desc}\n"

def array_end():
    return "}};\n\n"

def array_make(items, name, key):
    res = array_begin(name, len(items))
    for item in items:
        res += array_value(key(item), item.desc)
    res += array_end()
    return res


def header_begin(guard):
    return f"""#pragma once

#ifndef {guard}
#define {guard}

#include <array>

namespace utfcaseconv {{\nnamespace utf32 {{

"""

def header_end():
    return """}\n}
#endif

"""

def output_write(path_out, items):
    guard = "_UTFCASECONV_UTF32_TABLES_H_"
    upper = lambda item: item.upper
    lower = lambda item: item.lower

    with open_w(path_out) as f:
        f = open_w(path_out)
        f.write(header_begin(guard))

        items.sort(key=upper)
        f.write(array_make(items, "upper_lower_src_tbl", upper))
        f.write(array_make(items, "upper_lower_dst_tbl", lower))

        items.sort(key=lower)
        f.write(array_make(items, "lower_upper_src_tbl", lower))
        f.write(array_make(items, "lower_upper_dst_tbl", upper))

        f.write(header_end())


def input_parse(path_in):
    items = []

    with open_r(path_in) as f:
        for line in f:
            if line[0] == "#":
                continue

            tokens = line.split("; ")
            if len(tokens) < 4 or (tokens[1] != "C" and tokens[1] != "S"):
                continue

            upper = int(tokens[0], 16)
            lower = int(tokens[2], 16)
            desc = tokens[3].replace("CAPITAL ", "").replace("# ", "").strip()
            items.append(CaseconvItem(upper, lower, desc))

    return items


parser = argparse.ArgumentParser()
parser.add_argument("-i", "--input", help="Input CaseFolding.txt", type=str)
parser.add_argument("-o", "--output", help="Output header", type=str)
args = parser.parse_args()

items = input_parse(args.input)
output_write(args.output, items)
