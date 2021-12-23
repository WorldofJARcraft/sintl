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

cmake_minimum_required (VERSION 2.8.11)

project(sintl)

set(SINTL_MAJOR_VERSION "0")
set(SINTL_MINOR_VERSION "1")
set(SINTL_PATCH_VERSION "1")

# the sintl library
add_subdirectory(libsintl)
# the sintl headers
add_subdirectory(include)
# the gettext / ngettext utilities
add_subdirectory(gettext)
# the msgfmt utilities
add_subdirectory(msgfmt)
# the xgettext utility
add_subdirectory(xgettext)