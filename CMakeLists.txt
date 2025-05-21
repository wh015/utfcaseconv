cmake_minimum_required(VERSION 3.7)

project(utfcaseconv LANGUAGES CXX)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

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

set(BINARY_HEADERS_DIR "${CMAKE_BINARY_DIR}/include/utfcaseconv")
set(SOURCE_HEADERS_DIR "${CMAKE_SOURCE_DIR}/include/utfcaseconv")
set(TARGET_HEADERS
    "${SOURCE_HEADERS_DIR}/utf8.h"
    "${SOURCE_HEADERS_DIR}/utf8_constants.h"
    "${SOURCE_HEADERS_DIR}/utf32.h"
    "${BINARY_HEADERS_DIR}/utf32_tables.h"
)

add_custom_command(OUTPUT "${BINARY_HEADERS_DIR}/utf32_tables.h"
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${BINARY_HEADERS_DIR}"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/tools/gentables.py" -i "${CMAKE_SOURCE_DIR}/assets/CaseFolding.txt" -o "${BINARY_HEADERS_DIR}/utf32_tables.h"
    DEPENDS "${CMAKE_SOURCE_DIR}/assets/CaseFolding.txt" "${CMAKE_SOURCE_DIR}/tools/gentables.py"
    COMMENT "Making headers"
    VERBATIM
)

add_custom_target(generate_tables ALL DEPENDS "${BINARY_HEADERS_DIR}/utf32_tables.h")

add_library(utfcaseconv INTERFACE ${TARGET_HEADERS})
target_include_directories(utfcaseconv INTERFACE "${CMAKE_BINARY_DIR}/include")
target_include_directories(utfcaseconv INTERFACE "${CMAKE_SOURCE_DIR}/include")

include(GNUInstallDirs)
install(
    FILES ${TARGET_HEADERS}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/utfcaseconv")

if(WITH_TESTS OR WITH_BENCHMARKS)
    enable_testing()
if(WITH_TESTS)
    add_subdirectory("${CMAKE_SOURCE_DIR}/tests")
endif()
if(WITH_BENCHMARKS)
    add_subdirectory("${CMAKE_SOURCE_DIR}/benchmarks")
endif()
endif()
