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
#include <locale.h>
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

#define HAVE_QUERYLOCALE_OR_GETLOCALENAME_L (defined(HAVE_GETLOCALENAME_L) || defined(HAVE_QUERYLOCALE))
#define HAVE_USABLE_USELOCALE (defined(HAVE_USELOCALE) && HAVE_QUERYLOCALE_OR_GETLOCALENAME_L)

// without these interfaces, there is no way of mapping a locale_t to a locale name 
#if HAVE_USABLE_USELOCALE
static char *libsintl_locale_to_char(int category, locale_t locale){
    #ifdef HAVE_GETLOCALENAME_L
        // this new interface allows portably mapping locale to name, see https://www.austingroupbugs.net/view.php?id=1220
        // preferable over querylocale even if both exist, since no mapping of LC_* to LC_*_MASK needed
        // LC_GLOBAL_LOCALE is unspecified, but it cannot be used by the gettext functions anyway
        return getlocalename_l(category, locale);
    #elif defined(HAVE_QUERYLOCALE)
        // e.g. LC_CTYPE -> LC_CTYPE_MASK
        #define QUERYLOCALE_BITMAP_CASE(locale_type) #ifdef locale_type \
            case locale_type: \
                return querylocale(locale_type##_MASK, locale); \
            endif
        
        switch (category)
        {
        QUERYLOCALE_BITMAP_CASE(LC_CTYPE);
        QUERYLOCALE_BITMAP_CASE(LC_NUMERIC);
        QUERYLOCALE_BITMAP_CASE(LC_TIME);
        QUERYLOCALE_BITMAP_CASE(LC_COLLATE);
        QUERYLOCALE_BITMAP_CASE(LC_MONETARY);
        QUERYLOCALE_BITMAP_CASE(LC_PAPER);
        QUERYLOCALE_BITMAP_CASE(LC_NAME);
        QUERYLOCALE_BITMAP_CASE(LC_ADDRESS);
        QUERYLOCALE_BITMAP_CASE(LC_TELEPHONE);
        QUERYLOCALE_BITMAP_CASE(LC_MEASUREMENT);
        QUERYLOCALE_BITMAP_CASE(LC_IDENTIFICATION);
        // LC_MESSAGES needs to exist, and it is a suitable default
        default:
            return querylocale(LC_MESSAGES_MASK, locale);
        }
    #endif
        // never reached
}
#endif

static char *libsintl_query_locale(int category){
#if HAVE_USABLE_USELOCALE
    locale_t thread_locale = uselocale(NULL);
    if(thread_locale != LC_GLOBAL_LOCALE){
    // results unspecified for LC_GLOBAL_LOCALE
        return libsintl_locale_to_char(category, thread_locale);
    }
    // if no locale set for this thread, we need to query the global locale from setlocale
    
#endif
    return setlocale(category, NULL);
}
#endif