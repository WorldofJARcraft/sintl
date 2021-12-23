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

add_executable(gettext gettext.c)

target_include_directories(gettext PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_link_libraries(gettext sintl)

# ngettext can be a hardlink to gettext
ADD_CUSTOM_TARGET(ngettext ALL
                  COMMAND ${CMAKE_COMMAND} -E create_symlink ngettext gettext)