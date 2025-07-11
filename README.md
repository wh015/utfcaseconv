## Description
`utfcaseconv` — header-only library for caswfolding of `UTF-32` / `UTF-8` string and symbols  on Little Endian architectures.

## Purpose
Library is header-only and lightweight. It's supposed to be use when [ICU](https://icu.unicode.org) is overkill for your purposes.

## How it works
Using static tables to make a match between corresponding `UTF-32` symbols. If we find a symbol in one table, it has a pair with the same index in another, that symbol will be the result of casefolding.

File `assets/CaseFolding.txt` from https://www.unicode.org is used as a source for matching tables, it's transformed into multiple `std::array` during build process via simple Python script.

During `UTF-8` string casefolding the input string is additionaly separated into codepoints via [DFA](https://en.wikipedia.org/wiki/Deterministic_finite_automaton) to do the same lookup to `UTF-32` tables.

## Updaing tables
Current version is taken from [there](https://www.unicode.org/Public/16.0.0/ucd/CaseFolding.txt). There are only few case-sensitive alphabets, but if new one is added into the standard, then:

1. Go to [official Unicode resourse](https://www.unicode.org/Public).
2. Choose the necessary version. Current: [16.0.0](https://www.unicode.org/Public/16.0.0).
3. The necessary file is placed insude `ucd` directory and called `CaseFolding.txt`. Download the fike and replace `assets/CaseFolding.txt` in repository.
4. Commit. The headers are generated dueing each build.
5. Do not forget to update README and change a version to the new one.

## TODO
1. Better CPU detection support including runtime.
2. Support AVX / AVX2 / AVX512.

