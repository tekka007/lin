/*
 * GPL LICENSE SUMMARY
 * Copyright (c) 2011, Intel Corporation and its suppliers.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */
/*
	A simple sample code to maintain 32MB memory space
*/
/*
 * Split memmory with 8KB size
*/
#ifndef EMALLOC_H
#define EMALLOC_H


#include <linux/module.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/vmalloc.h>
#include <linux/pagemap.h>
#include <linux/delay.h>
#include <linux/netdevice.h>
#include <linux/tcp.h>
#include <linux/ipv6.h>
#include <linux/slab.h>
#include <net/checksum.h>
#include <net/ip6_checksum.h>
#include <linux/mii.h>
#include <linux/ethtool.h>
#include <linux/if_vlan.h>
#include <linux/cpu.h>
#include <linux/smp.h>
#include <linux/pm_qos_params.h>
#include <linux/pm_runtime.h>
#include <linux/aer.h>

#define E1000E_PAGE_SIZE  (4 * 1024)

/*
	 PCIE restricted region is set in 606 ~ 638Mbyte
	 PCIE restricted region is set in 384 ~ 416Mbyte
	 PCIE restricted region is set in 384 ~ 392Mbyte
	 PCIE restricted region is set in 384 ~ 385Mbyte 20111108
	 PCIE restricted region is set in 415 ~ 419Mbyte 20130621 to fix no space left issue
*/
#define E1000E_LIMIT_MEM_SIZE (4*1024*1024)
#define E1000E_LIMIT_MEM_BASE (415*1024*1024)


extern void* acquire_emalloc_static(int i32Size);
extern void* emalloc(int i32Size);

extern void efree(void* to_be_free);
extern void *__e_virt_to_phy (volatile void *);

#define EMALLOC_ON_ERROR 1 /* gu9gu 20111108 */
#ifdef EMALLOC_ON_ERROR /* gu9gu 20111108 */
extern int is_emalloc_v(volatile unsigned char *vaddr);
extern int is_emalloc_p(volatile dma_addr_t address);
#endif /* EMALLOC_ON_ERROR */


extern void efreeall(void);

#endif

