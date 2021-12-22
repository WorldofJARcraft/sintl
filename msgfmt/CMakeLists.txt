find_package(BISON)
find_package(FLEX)

bison_target(gnu_po gnu_po.y ${CMAKE_CURRENT_BINARY_DIR}/gnu_po.tab.c)
flex_target(xgettext_lex xgettext.lx.l  ${CMAKE_CURRENT_BINARY_DIR}/xgettext_lex.c)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND GNU_SOURCES gnu_msgfmt.c gnu_handle.c gnu_lex.c gnu_hash.c gnu_check.c)
list(APPEND GNU_MSGS_SOURCES gnu_msgs.c)
list(APPEND GNU_MSGS_REV_SOURCES gnu_msgs_rev.c)


list(APPEND SOLARIS_SOURCES msgfmt.c check_header.c)

list(APPEND COMMON_SOURCES option.c util.c)

list(APPEND XGETTEXT_SOURCES xgettext.c)

add_executable(msgfmt ${GNU_SOURCES} ${BISON_gnu_po_OUTPUTS} ${GNU_MSGS_SOURCES} ${COMMON_SOURCES})
add_executable(msgfmt_rev ${GNU_SOURCES} ${BISON_gnu_po_OUTPUTS} ${GNU_MSGS_REV_SOURCES} ${COMMON_SOURCES})

add_executable(smsgfmt ${SOLARIS_SOURCES} ${COMMON_SOURCES})

add_executable(xgettext ${XGETTEXT_SOURCES} ${FLEX_xgettext_lex_OUTPUTS})

target_include_directories(msgfmt PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_include_directories(msgfmt_rev PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_include_directories(smsgfmt PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")


include(${CMAKE_CURRENT_SOURCE_DIR}/../config/CMakeLists.txt)

configure_libsintl(sintl)