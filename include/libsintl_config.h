/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright 2021 Eric Ackermann.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _libsintl_config_h
#define _libsintl_config_h

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// original Solaris code uses fstat64(), which is not portable to e.g. Linux
#ifdef HAVE_STAT64
typedef struct stat64 libsintl_statbuf;
#define libsintl_fstat64 fstat64
#else
typedef struct stat libsintl_statbuf;
#define libsintl_fstat64 fstat
#endif

static int libsintl_naive_issetugid(void){
        return getuid() != geteuid() || getgid() != getegid();
}

#if defined(HAVE_GETAUXVAL)
    
    #include <sys/auxv.h>
    #include <errno.h>

    #ifdef AT_SECURE
    static int libsintl_issetugid(void){
        // returns positive value if setuid / setgid is set by process.
        // returns 0 if setuid / setgid was not set or the AT_SECURE variable was not set.
        // newer versions of libc set ENOENT if the variable does not exist, in this case we assume the worst case (setuid / setgid set)
        return getauxval(AT_SECURE) ||  errno == ENOENT;
    }
    #elif defined(AT_RUID) && defined (AT_EUID) && defined (AT_RGID) && defined (AT_EGID)
    // assume worst case by default - we are setuid / setgid
    #define GET_AUXVAL_OR_RETURN_ONE(target, auxval) if((target = getauxval(auxval)) == 0 && errno == ENOENT){return 1;}
    // no AT_SECURE - determine the same by checking UID / GID and effective UID / GID
    static int libsintl_issetugid(void){
        uid_t real_uid, effective_uid;
        gid_t real_gid, effective_gid;
        errno = 0;

        GET_AUXVAL_OR_RETURN_ONE(real_uid, AT_RUID)
        GET_AUXVAL_OR_RETURN_ONE(effective_uid, AT_EUID)
        GET_AUXVAL_OR_RETURN_ONE(real_gid, AT_RGID)
        GET_AUXVAL_OR_RETURN_ONE(effective_gid, AT_EGID)
        
        return real_uid != effective_uid || real_gid != effective_gid;
    }
    #else
        #define libsintl_issetugid libsintl_naive_issetugid
    #endif
#elif defined(HAVE_ISSETUGID)
    #define libsintl_issetugid issetugid
#else
    #define libsintl_issetugid libsintl_naive_issetugid
#endif
#endif