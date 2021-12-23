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
 * Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */


#ifndef	_LIBINTL_H
#define	_LIBINTL_H

#pragma ident	"%Z%%M%	%I%	%E% SMI"

#include <locale.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define	TEXTDOMAINMAX	256

#define	__GNU_GETTEXT_SUPPORTED_REVISION(m)	\
	((((m) == 0) || ((m) == 1)) ? 1 : -1)

#ifdef __STDC__
extern char *dcgettext(const char *, const char *, const int);
extern char *dgettext(const char *, const char *);
extern char *gettext(const char *);
extern char *textdomain(const char *);
extern char *bindtextdomain(const char *, const char *);

/*
 * LI18NUX 2000 Globalization Specification Version 1.0
 * with Amendment 2
 */
extern char *dcngettext(const char *, const char *,
	const char *, unsigned long int, int);
extern char *dngettext(const char *, const char *,
	const char *, unsigned long int);
extern char *ngettext(const char *, const char *, unsigned long int);
extern char *bind_textdomain_codeset(const char *, const char *);

/*
 * To be added in POSIX issue 8, see https://posix.rhansen.org/p/gettext_draft
 */
extern char *dcgettext_l(const char *restrict, const char *restrict, 
	int, locale_t);
extern char *dcngettext_l(const char *restrict, const char *restrict, 
	const char *restrict, unsigned long int, int, locale_t);
extern char *dgettext_l(const char *restrict, const char *restrict,
	locale_t);
extern char *dngettext_l(const char *restrict, const char *restrict,
	const char *restrict, unsigned long int, locale_t);
extern char *gettext_l(const char *, locale_t);
extern char *ngettext_l(const char *restrict, const char *restrict,
	unsigned long int, locale_t);

#else
extern char *dcgettext();
extern char *dgettext();
extern char *gettext();
extern char *textdomain();
extern char *bindtextdomain();

/*
 * LI18NUX 2000 Globalization Specification Version 1.0
 * with Amendment 2
 */
extern char *dcngettext();
extern char *dngettext();
extern char *ngettext();
extern char *bind_textdomain_codeset();

/*
 * To be added in POSIX issue 8, see https://posix.rhansen.org/p/gettext_draft
 */
extern char *dcgettext_l();
extern char *dcngettext_l();
extern char *dgettext_l();
extern char *dngettext_l();
extern char *gettext_l();
extern char *ngettext_l();
#endif

#ifdef	__cplusplus
}
#endif

#endif /* _LIBINTL_H */
