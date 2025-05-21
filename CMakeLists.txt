cmake_minimum_required(VERSION 3.7)

project(utf32caseconv LANGUAGES CXX VERSION 0.0.1)

set (TARGET_HEADERS
    "${CMAKE_BINARY_DIR}/include/utf32caseconv/utf32caseconv.h"
    "${CMAKE_BINARY_DIR}/include/utf32caseconv/utf32caseconv_tables.h"
)

add_custom_command(OUTPUT ${TARGET_HEADERS}
  COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/include/utf32caseconv.h" "${CMAKE_BINARY_DIR}/include/utf32caseconv/utf32caseconv.h"
  COMMAND python3 "${CMAKE_SOURCE_DIR}/tools/gentables.py" -i "${CMAKE_SOURCE_DIR}/assets/CaseFolding.txt" -o "${CMAKE_BINARY_DIR}/include/utf32caseconv/utf32caseconv_tables.h"
  DEPENDS "${CMAKE_SOURCE_DIR}/assets/CaseFolding.txt" "${CMAKE_SOURCE_DIR}/tools/gentables.py" "${CMAKE_SOURCE_DIR}/include/utf32caseconv.h"
  COMMENT "Making headers"
  VERBATIM
)

add_custom_target(generate_tables ALL DEPENDS ${TARGET_HEADERS})

add_library(utf32caseconv INTERFACE)
target_include_directories(utf32caseconv INTERFACE "${CMAKE_SOURCE_DIR}/include")

include(GNUInstallDirs)
install(
    FILES ${TARGET_HEADERS}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/utf32caseconv")
