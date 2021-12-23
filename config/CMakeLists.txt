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

function (configure_libsintl targetName)
    include(CheckSymbolExists)

    check_symbol_exists(fstat64 "sys/stat.h" HAVE_FSTAT64)
    check_symbol_exists(getauxval "sys/auxv.h" HAVE_GETAUXVAL)
    check_symbol_exists(issetugid "unistd.h" HAVE_ISSETUGID)
    check_symbol_exists(uselocale "locale.h" HAVE_USELOCALE)
    check_symbol_exists(getlocalename_l "locale.h" HAVE_GETLOCALENAME_L)
    check_symbol_exists(querylocale "locale.h" HAVE_QUERYLOCALE)


    set(ExtraCompileOptions "")

    if(${HAVE_FSTAT64})
        string(APPEND ExtraCompileOptions "-DHAVE_STAT64")
        message("Configuration options: Have fstat64: ${HAVE_FSTAT64}")
    else()
        message("Configuration options: Have fstat64: no")
    endif()

    if(${HAVE_GETAUXVAL})
        string(APPEND ExtraCompileOptions "-DHAVE_GATAUXVAL")
        message("Configuration options: Have getauxval: ${HAVE_GETAUXVAL}")
    else()
        message("Configuration options: Have getauxval: no")
    endif()

    if(${HAVE_ISSETUGID})
        string(APPEND ExtraCompileOptions "-DHAVE_ISSETUGID")
        message("Configuration options: Have issetugid: ${HAVE_ISSETUGID}")
    else()
        message("Configuration options: Have issetugid: no")
    endif()

    if(${HAVE_USELOCALE})
        if(${HAVE_GETLOCALENAME_L})
            string(APPEND ExtraCompileOptions "-DHAVE_USELOCALE -DHAVE_GETLOCALENAME_L")
            message("Configuration options: Have uselocale: 1")
            message("Configuration options: Have getlocalename_l: 1")
        elseif(${HAVE_QUERYLOCALE})
            string(APPEND ExtraCompileOptions "-DHAVE_USELOCALE -DHAVE_QUERYLOCALE")
            message("Configuration options: Have uselocale: 1")
            message("Configuration options: Have querylocale: 1")
        else()
            message("Configuration options: Have uselocale: 0")
            message("Have uselocale but no getlocalename_l or querylocale - cannot map selected locale to name!")
        endif()
    else()
        message("Configuration options: Have working uselocale: 0")
        message("Do not have uselocale!")
    endif()

    target_compile_options(${targetName} PRIVATE ${ExtraCompileOptions})
endfunction()