#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright 2021 Eric Ackermann.  All rights reserved.
# Use is subject to license terms.
#

find_package(BISON)

bison_target(gnu_po gnu_po.y ${CMAKE_CURRENT_BINARY_DIR}/gnu_po.tab.c)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND GNU_SOURCES gnu_msgfmt.c gnu_handle.c gnu_lex.c gnu_hash.c gnu_check.c)
list(APPEND GNU_MSGS_SOURCES gnu_msgs.c)
list(APPEND GNU_MSGS_REV_SOURCES gnu_msgs_rev.c)


list(APPEND SOLARIS_SOURCES msgfmt.c check_header.c)

list(APPEND COMMON_SOURCES option.c util.c)

add_executable(msgfmt ${GNU_SOURCES} ${BISON_gnu_po_OUTPUTS} ${GNU_MSGS_SOURCES} ${COMMON_SOURCES})
add_executable(msgfmt_rev ${GNU_SOURCES} ${BISON_gnu_po_OUTPUTS} ${GNU_MSGS_REV_SOURCES} ${COMMON_SOURCES})

add_executable(smsgfmt ${SOLARIS_SOURCES} ${COMMON_SOURCES})

target_include_directories(msgfmt PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_include_directories(msgfmt_rev PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_include_directories(smsgfmt PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")


include(${CMAKE_CURRENT_SOURCE_DIR}/../config/CMakeLists.txt)

configure_libsintl(sintl)