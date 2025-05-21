cmake_minimum_required(VERSION 3.7)

project(utfcaseconv LANGUAGES CXX)

if (NOT DEFINED Python3_EXECUTABLE)
    set(Python3_EXECUTABLE "python3")
endif()

include_directories(BEFORE SYSTEM ${CMAKE_INCLUDE_PATH})

option(WITH_TESTS "Build common tests." ON)

if(MSVC)
    add_compile_options(
        /utf-8 # to support multibyte char literals in tests
    )
endif()

set (TARGET_HEADERS
    "${CMAKE_BINARY_DIR}/include/utfcaseconv/utf8.h"
    "${CMAKE_BINARY_DIR}/include/utfcaseconv/utf32.h"
    "${CMAKE_BINARY_DIR}/include/utfcaseconv/utf32_tables.h"
)

add_custom_command(OUTPUT ${TARGET_HEADERS}
    COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_SOURCE_DIR}/include/utf32.h" "${CMAKE_BINARY_DIR}/include/utfcaseconv/utf32.h"
    COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_SOURCE_DIR}/include/utf8.h" "${CMAKE_BINARY_DIR}/include/utfcaseconv/utf8.h"
    COMMAND "python3" "${CMAKE_SOURCE_DIR}/tools/gentables.py" -i "${CMAKE_SOURCE_DIR}/assets/CaseFolding.txt" -o "${CMAKE_BINARY_DIR}/include/utfcaseconv/utf32_tables.h"
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

if(WITH_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
