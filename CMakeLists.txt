cmake_minimum_required(VERSION 3.7)

project(utfcaseconv LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON" FORCE)

if (NOT DEFINED Python3_EXECUTABLE)
    set(Python3_EXECUTABLE "python3")
endif()

include_directories(BEFORE SYSTEM ${CMAKE_INCLUDE_PATH})

option(WITH_TESTS "Build common tests." ON)
option(WITH_BENCHMARKS "Build benchmarks." OFF)

if(MSVC)
    add_compile_options(
        /utf-8 # to support multibyte char literals in tests
    )
endif()

set(TARGET_HEADERS_DIR "${CMAKE_BINARY_DIR}/include/utfcaseconv")
set(TARGET_HEADERS
    "${TARGET_HEADERS_DIR}/utf8.h"
    "${TARGET_HEADERS_DIR}/utf8_constants.h"
    "${TARGET_HEADERS_DIR}/utf32.h"
    "${TARGET_HEADERS_DIR}/utf32_tables.h"
)

add_custom_command(OUTPUT ${TARGET_HEADERS}
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${TARGET_HEADERS_DIR}"
    COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_SOURCE_DIR}/include/utf8.h" "${TARGET_HEADERS_DIR}/utf8.h"
    COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_SOURCE_DIR}/include/utf8_constants.h" "${TARGET_HEADERS_DIR}/utf8_constants.h"
    COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_SOURCE_DIR}/include/utf32.h" "${TARGET_HEADERS_DIR}/utf32.h"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/tools/gentables.py" -i "${CMAKE_SOURCE_DIR}/assets/CaseFolding.txt" -o "${TARGET_HEADERS_DIR}/utf32_tables.h"
    DEPENDS "${CMAKE_SOURCE_DIR}/assets/CaseFolding.txt" "${CMAKE_SOURCE_DIR}/tools/gentables.py" "${CMAKE_SOURCE_DIR}/include/utf32.h" "${CMAKE_SOURCE_DIR}/include/utf8.h"
    COMMENT "Making headers"
    VERBATIM
)

add_custom_target(generate_tables ALL DEPENDS ${TARGET_HEADERS})

add_library(utfcaseconv INTERFACE ${TARGET_HEADERS})
target_include_directories(utfcaseconv INTERFACE "${CMAKE_BINARY_DIR}/include")

include(GNUInstallDirs)
install(
    FILES ${TARGET_HEADERS}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/utfcaseconv")

if(WITH_TESTS OR WITH_BENCHMARKS)
    enable_testing()
if(WITH_TESTS)
    add_subdirectory(tests)
endif()
if(WITH_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()
endif()
