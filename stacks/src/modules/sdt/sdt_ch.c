/*****************************************************************************

 @(#) $RCSfile: sdt_ch.c,v $ $Name:  $($Revision: 0.9.2.2 $) $Date: 2007/08/14 12:18:45 $

 -----------------------------------------------------------------------------

 Copyright (c) 2001-2007  OpenSS7 Corporation <http://www.openss7.com/>
 Copyright (c) 1997-2000  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This program is free software: you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation, version 3 of the license.

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

 Last Modified $Date: 2007/08/14 12:18:45 $ by $Author: brian $

 -----------------------------------------------------------------------------

 $Log: sdt_ch.c,v $
 Revision 0.9.2.2  2007/08/14 12:18:45  brian
 - GPLv3 header updates

 Revision 0.9.2.1  2007/07/21 20:22:01  brian
 - added channel modules

 *****************************************************************************/

#ident "@(#) $RCSfile: sdt_ch.c,v $ $Name:  $($Revision: 0.9.2.2 $) $Date: 2007/08/14 12:18:45 $"

static char const ident[] =
    "$RCSfile: sdt_ch.c,v $ $Name:  $($Revision: 0.9.2.2 $) $Date: 2007/08/14 12:18:45 $";

/*
 * This is SDT-CH.  It is a pushable STREAMS module that can be pushed over a CH Stream providing
 * the Channel Interface (CHI) service interface instead of the normal Signalling Data Link
 * Interface (SDLI) service interface as is performed by the regular SDT module.
 *
 * There exists a conversion module (SDL-CH) that will convert a channel into a signalling data link
 * for the purposes of SS7 and using the regular SDT module; however, this approach might be more
 * efficient in the long run.  Performance testing will tell.
 */