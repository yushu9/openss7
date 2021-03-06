/*****************************************************************************

 @(#) src/include/sys/sun/strsun.h

 -----------------------------------------------------------------------------

 Copyright (c) 2008-2015  Monavacon Limited <http://www.monavacon.com/>
 Copyright (c) 2001-2008  OpenSS7 Corporation <http://www.openss7.com/>
 Copyright (c) 1997-2001  Brian F. G. Bidulock <bidulock@openss7.org>

 All Rights Reserved.

 This program is free software; you can redistribute it and/or modify it under
 the terms of the GNU Affero General Public License as published by the Free
 Software Foundation; version 3 of the License.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more
 details.

 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>, or
 write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA
 02139, USA.

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

 *****************************************************************************/

#ifndef __SYS_SUN_STRSUN_H__
#define __SYS_SUN_STRSUN_H__

#ifndef _SYS_STRSUN_H
#warning "Do not include sys/sun/strsun.h directly, include sys/strsun.h instead."
#endif

#ifndef __KERNEL__
#error "Do not use kernel headers for user space programs"
#endif				/* __KERNEL__ */

#ifndef __EXTERN_INLINE
#define __EXTERN_INLINE extern __inline__
#endif

#ifndef __SUN_EXTERN_INLINE
#define __SUN_EXTERN_INLINE __EXTERN_INLINE streamscall
#endif				/* __SUN_EXTERN_INLINE */

#ifndef __SUN_EXTERN
#define __SUN_EXTERN extern streamscall
#endif

#include <linux/types.h>

#if 0
__SUN_EXTERN_INLINE unsigned char *
DB_BASE(mblk_t *mp)
{
	return (unsigned char *) (mp->b_datap->db_base);
}
#endif
#ifndef DB_BASE
#define DB_BASE(mp) ((mp)->b_datap->db_base)
#endif
#if 0
__SUN_EXTERN_INLINE unsigned char *
DB_LIM(mblk_t *mp)
{
	return (unsigned char *) (mp->b_datap->db_lim);
}
#endif
#ifndef DB_LIM
#define DB_LIM(mp) ((mp)->b_datap->db_lim)
#endif
#if 0
__SUN_EXTERN_INLINE size_t
DB_REF(mblk_t *mp)
{
	return (size_t) (mp->b_datap->db_ref);
}
#endif
#ifndef DB_REF
#define DB_REF(mp) ((mp)->b_datap->db_ref)
#endif
#if 0
__SUN_EXTERN_INLINE int
DB_TYPE(mblk_t *mp)
{
	return (int) (mp->b_datap->db_type);
}
#endif
#ifndef DB_TYPE
#define DB_TYPE(mp) ((mp)->b_datap->db_type)
#endif

__SUN_EXTERN_INLINE long
MBLKL(mblk_t *mp)
{
	return (long) (mp->b_wptr - mp->b_rptr);
}
#ifndef MBLKL
#define MBLKL MBLKL
#endif
__SUN_EXTERN_INLINE long
MBLKSIZE(mblk_t *mp)
{
	return (long) (mp->b_datap->db_lim - mp->b_datap->db_base);
}
#ifndef MBLKSIZE
#define MBLKSIZE MBLKSIZE
#endif
__SUN_EXTERN_INLINE long
MBLKHEAD(mblk_t *mp)
{
	return (long) (mp->b_rptr - mp->b_datap->db_base);
}
#ifndef MBLKHEAD
#define MBLKHEAD MBLKHEAD
#endif
__SUN_EXTERN_INLINE long
MBLKTAIL(mblk_t *mp)
{
	return (long) (mp->b_datap->db_lim - mp->b_wptr);
}
#ifndef MBLKTAIL
#define MBLKTAIL MBLKTAIL
#endif
__SUN_EXTERN_INLINE long
MBLKIN(mblk_t *mp, ssize_t off, size_t len)
{
	return ((off >= 0) && (mp->b_rptr + off + len <= mp->b_wptr));
}
#ifndef MBLKIN
#define MBLKIN MBLKIN
#endif
__SUN_EXTERN_INLINE long
OFFSET(void *p, void *base)
{
	return (long) ((caddr_t) p - (caddr_t) base);
}
#ifndef OFFSET
#define OFFSET OFFSET
#endif

__SUN_EXTERN_INLINE void
merror(queue_t *q, mblk_t *mp, int error)
{
	mp->b_datap->db_type = M_ERROR;
	mp->b_rptr = mp->b_wptr = mp->b_datap->db_base;
	mp->b_wptr += 2;
	mp->b_rptr[0] = mp->b_rptr[1] = error;
	qreply(q, mp);
}
static __inline__ streamscall void
mioc2ack(mblk_t *mp, mblk_t *db, size_t count, int rval)
{
	union ioctypes *iocp;

	mp->b_datap->db_type = M_IOCACK;
	iocp = (typeof(iocp)) mp->b_rptr;
	iocp->iocblk.ioc_count = count;
	iocp->iocblk.ioc_rval = rval;
	iocp->iocblk.ioc_error = 0;
	if (mp->b_cont)
		freemsg(xchg(&mp->b_cont, db));
	else
		mp->b_cont = db;
	if (mp->b_cont)
		mp->b_cont->b_wptr = mp->b_cont->b_rptr + count;
}
__SUN_EXTERN_INLINE void
miocack(queue_t *q, mblk_t *mp, int count, int rval)
{
	union ioctypes *iocp;

	mp->b_datap->db_type = M_IOCACK;
	iocp = (typeof(iocp)) mp->b_rptr;
	iocp->iocblk.ioc_count = count;
	iocp->iocblk.ioc_rval = rval;
	iocp->iocblk.ioc_error = 0;
	qreply(q, mp);
}
__SUN_EXTERN_INLINE void
miocnak(queue_t *q, mblk_t *mp, int count, int error)
{
	union ioctypes *iocp;

	mp->b_datap->db_type = M_IOCNAK;
	iocp = (typeof(iocp)) mp->b_rptr;
	iocp->iocblk.ioc_count = count;
	iocp->iocblk.ioc_rval = -1;
	iocp->iocblk.ioc_error = error;
	qreply(q, mp);
}
static __inline__ streamscall mblk_t *
mexchange(queue_t *q, mblk_t *mp, size_t size, int type, uint32_t primtype)
{
	if (unlikely(mp == NULL ||
		     (size > FASTBUF && mp->b_datap->db_lim - mp->b_datap->db_base < size) ||
		     mp->b_datap->db_ref > 1 || mp->b_datap->db_frtnp != NULL)) {
		/* can't reuse this message block (or no message block to begin with) */
		if (mp)
			freemsg(mp);
		if (!(mp = allocb(size, BPRI_LO))) {
			if (q && (mp = allocb(2, BPRI_HI)))
				merror(q, mp, ENOSR);
			return (NULL);
		}
	} else {
		/* prepare existing message block for reuse */
		mp->b_next = mp->b_prev = NULL;
		if (mp->b_cont)
			freemsg(xchg(&mp->b_cont, NULL));
		mp->b_rptr = mp->b_datap->db_base;
		mp->b_band = 0;
		mp->b_flag = 0;
	}
	/* we now have a usable message block */
	mp->b_datap->db_type = type;
	mp->b_wptr = mp->b_rptr + size;
	if (primtype >= 0 && size >= sizeof(uint32_t))
		*(uint32_t *) mp->b_rptr = primtype;
	return (mp);
}
__SUN_EXTERN_INLINE mblk_t *
mexpandb(mblk_t *mp, int i1, int i2)
{
	/* I don't really know what this does... */
	return (NULL);
}
__SUN_EXTERN_INLINE int
miocpullup(mblk_t *mp, size_t len)
{
	if (unlikely(!mp || !mp->b_cont ||
		     ((struct iocblk *) mp->b_rptr)->ioc_count == TRANSPARENT))
		goto einval;
	if (pullupmsg(mp->b_cont, len))
		return (0);
	if (msgdsize(mp->b_cont) < len)
		goto einval;
	return (ENOSR);
      einval:
	return (EINVAL);
}

#if 0
/* contained in the base package */
__SUN_EXTERN_INLINE size_t
msgsize(mblk_t *mp)
{
	mblk_t *bp;
	size_t s;

	for (bp = mp, s = 0; bp; bp = bp->b_cont) {
		if (bp->b_wptr > bp->b_rptr) {
			s += bp->b_wptr - bp->b_rptr;
		}
	}
	return s;
}
#endif
static __inline__ streamscall void
mcopymsg(mblk_t *mp, unsigned char *buf)
{
	mblk_t *bp;
	unsigned char *ptr;

	for (bp = mp, ptr = buf; bp; bp = bp->b_cont) {
		if (bp->b_wptr > bp->b_rptr) {
			long len = bp->b_wptr - bp->b_rptr;

			bcopy(bp->b_rptr, ptr, len);
			ptr += len;
		}
	}
	freemsg(mp);
	return;
}
static __inline__ streamscall void
mcopyin(mblk_t *mp, void *priv, size_t size, void *uaddr)
{
	union ioctypes *iocp = (typeof(iocp)) mp->b_rptr;

	if (mp->b_datap->db_type == M_IOCTL && iocp->iocblk.ioc_count == TRANSPARENT)
		iocp->copyreq.cq_addr = (caddr_t) (long) *(intptr_t *)mp->b_cont->b_rptr;
	else
		iocp->copyreq.cq_addr = (caddr_t) uaddr;
	if (mp->b_cont)
		freemsg(xchg(&mp->b_cont, NULL));
	mp->b_datap->db_type = M_COPYIN;
	iocp->copyreq.cq_private = (mblk_t *) priv;
	iocp->copyreq.cq_size = size;
	iocp->copyreq.cq_flag = 0;
	mp->b_wptr = mp->b_rptr + sizeof(iocp->copyreq);
}
static __inline__ streamscall void
mcopyout(mblk_t *mp, void *priv, size_t size, void *uaddr, mblk_t *dp)
{
	union ioctypes *iocp = (typeof(iocp)) mp->b_rptr;

	if (mp->b_datap->db_type == M_IOCTL && iocp->iocblk.ioc_count == TRANSPARENT) {
		iocp->copyreq.cq_addr = (caddr_t) (long) *(intptr_t *)mp->b_cont->b_rptr;
		freemsg(xchg(&mp->b_cont, dp));
	} else {
		iocp->copyreq.cq_addr = (caddr_t) uaddr;
		if (dp) {
			if (mp->b_cont)
				freemsg(xchg(&mp->b_cont, dp));
			else
				mp->b_cont = dp;
		}
	}
	mp->b_datap->db_type = M_COPYOUT;
	iocp->copyreq.cq_private = (mblk_t *) priv;
	iocp->copyreq.cq_size = size;
	iocp->copyreq.cq_flag = 0;
	mp->b_wptr = mp->b_rptr + sizeof(iocp->copyreq);
	mp->b_cont->b_wptr = mp->b_cont->b_rptr + size;
}

#endif				/* __SYS_SUN_STRSUN_H__ */
