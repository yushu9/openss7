/*****************************************************************************

 @(#) $Id$

 -----------------------------------------------------------------------------

 Copyright (c) 2001-2007  OpenSS7 Corporation <http://www.openss7.com/>
 Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation; version 3 of the License.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 details.

 You should have received a copy of the GNU General Public License along with
 this program.  If not, see <http://www.gnu.org/licenses/>, or write to the
 Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

 -----------------------------------------------------------------------------

 U.S. GOVERNMENT RESTRICTED RIGHTS.  If you are licensing this Software on
 behalf of the U.S. Government ("Government"), the following provisions apply
 to you.  If the Software is supplied by the Department of Defense ("DoD"), it
 is classified as "Commercial Computer Software" under paragraph 252.227-7014
 of the DoD Supplement to the Federal Acquisition Regulations ("DFARS") (or any
 successor regulations) and the Government is acquiring only the license rights
 granted herein (the license rights customarily provided to non-Government
 users).  If the Software is supplied to any unit or agency of the Government
 other than DoD, it is classified as "Restricted Computer Software" and the
 Government's rights in the Software are defined in paragraph 52.227-19 of the
 Federal Acquisition Regulations ("FAR") (or any successor regulations) or, in
 the cases of NASA, in paragraph 18.52.227-86 of the NASA Supplement to the FAR
 (or any successor regulations).

 -----------------------------------------------------------------------------

 Commercial licensing and support of this software is available from OpenSS7
 Corporation at a fee.  See http://www.openss7.com/

 -----------------------------------------------------------------------------

 Last Modified $Date$ by $Author$

 -----------------------------------------------------------------------------

 $Log$
 *****************************************************************************/

#ifndef __ISODE_USR_DIRENT_H__
#define __ISODE_USR_DIRENT_H__

#ident "@(#) $RCSfile$ $Name$($Revision$) Copyright (c) 2001-2007 OpenSS7 Corporation."

/*
 *  Autoconf should make most of this go away.  FIXME: do that. --bb (2007-10-21)
 */

/* usr.dirent.h - ISODE's version of DAG's SVR3 directory access routines */

/*
	<dirent.h> -- definitions for SVR3 directory access routines

	last edit:	25-Apr-1987	D A Gwyn

	Prerequisite:	<sys/types.h>
*/

#ifndef	_CONFIG_
#include "config.h"		/* system-specific configuration */
#endif
#ifndef	GETDENTS
#if	defined(SUNOS4)
#define	GETDENTS
#endif
#endif

#ifdef	GETDENTS
#include <dirent.h>
#else
#include	"sys.dirent.h"

#define	DIRBUF		8192	/* buffer size for fs-indep. dirs */
	/* must in general be larger than the filesystem buffer size */

typedef struct {
	int dd_fd;			/* file descriptor */
	int dd_loc;			/* offset in block */
	int dd_size;			/* amount of valid data */
	char *dd_buf;			/* -> directory block */
} DIR;					/* stream data from opendir() */

#define	opendir		_opendir
#define	readdir		_readdir
#define	telldir		_telldir
#define	seekdir		_seekdir
#define	rewinddir	_rewinddir
#define	closedir	_closedir

extern DIR *opendir();
extern struct dirent *readdir();
extern off_t telldir();
extern void seekdir();
extern void rewinddir();
extern int closedir();

#ifndef NULL
#define	NULL	0		/* DAG -- added for convenience */
#endif
#endif				/* not GETDENTS */

#define	getcwd		_getcwd

extern char *getcwd();

#define	scandir	_scandir
#define	alphasort _alphasort

extern char *direntversion;

#endif				/* __ISODE_USR_DIRENT_H__ */