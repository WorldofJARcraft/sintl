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

find_package(FLEX)

flex_target(xgettext_lex xgettext.lx.l  ${CMAKE_CURRENT_BINARY_DIR}/xgettext_lex.c)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND XGETTEXT_SOURCES xgettext.c)

add_executable(xgettext ${XGETTEXT_SOURCES} ${FLEX_xgettext_lex_OUTPUTS})