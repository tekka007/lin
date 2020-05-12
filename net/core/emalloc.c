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
	A simple sample code to maintain 8MB memory space
*/
/*
 * Split memmory with 8KB size
*/
#include <linux/emalloc.h>

#define EMALLOC_ON_ERROR 1 /* gu9gu 20111108 */
#define EM_ATOMIC_CHECK

//#define ENABLE_EMALLOC_DEBUG_COUNT_PRINT

#ifdef ENABLE_EMALLOC_DEBUG_COUNT_PRINT /* yuvaraja.mg */
	//#define DEBUG_ALL_EMALLOC
	#define DEBUG_MAX_COUNT_ONLY
#endif /* yuvaraja.mg - ENABLE_EMALLOC_DEBUG_COUNT_PRINT */

#ifdef DEBUG_ALL_EMALLOC /* yuvaraja.mg */
	#define ENABLE_EMALLOC_DEBUG_COUNT_PRINT_THRES	250
#endif /* yuvaraja.mg - DEBUG_ALL_EMALLOC */

#ifndef EM_ATOMIC_CHECK /* gu9gu 20111020 */
static volatile u8 *memory_flags;
#else /* it has bugs */
static atomic_t *memory_flags;
#endif

//#define RCU_SPINLOCK_20111021 /* gu9gu 20111021 */
#ifdef RCU_SPINLOCK_20111021 /* gu9gu 20111021 */
DEFINE_SPINLOCK(memoryflagsmutex);
#endif

static u32 flag_num;

static u8 *skb_base_addr;

static u32 max_address;

static unsigned long e1000e_rx_mem_virt_base = 0; //NULL;
#if 1 /* gu9gu 20111024 */
static int previous_free_memory_index = 0;
#endif

#if 0 /* gu9gu 20111020 */
static int ioremap_init = 0;
#else
static atomic_t initialized = ATOMIC_INIT(1);
#endif

/* {{{ yuvaraja.mg - for debugging date="Tuesday, June 04, 2013";time="1:32:51 PM";year="2013";month="6";dayofweek="2";day="4";hour="13";minute="32";second="51";milliseconds="764";  */
#ifdef ENABLE_EMALLOC_DEBUG_COUNT_PRINT /* yuvaraja.mg */

static int emalloc_count = 0;

#ifdef DEBUG_MAX_COUNT_ONLY /* yuvaraja.mg */
static int emalloc_max_count = 0;
#endif /* yuvaraja.mg - DEBUG_MAX_COUNT_ONLY */

#endif /* yuvaraja.mg - ENABLE_EMALLOC_DEBUG_COUNT_PRINT */
/* }}} yuvaraja.mg - for debugging 1:32:51 PM */

//#define ENABLE_NO_OF_SAME_PACKET_SIZE_COUNT_TRACE

#ifdef ENABLE_NO_OF_SAME_PACKET_SIZE_COUNT_TRACE /* yuvaraja.mg */
typedef struct tagAllocInfo {
	int	m_i32Size;
	int	m_i32Count;
} STRUCT_ALLOCINFO;

typedef struct tagMemoryAllocSizeTrace {
	char				m_ai8TraceName[ 20 ];	// To identify which trace info

	int					m_i32ArraySize;		// Total no. of entries possible in Alloc Info array
	STRUCT_ALLOCINFO	*m_pastAllocInfo;	// Array of Alloc Info entries
	int					m_i32NoOfEntriesAdded;	// To maintain no of entries in Alloc Info array

	int					m_i32MaxSizeReceived;	// TO know the maximum size of alloc request

	int					m_i32PrintThres;	// Print Threshold to avoid issues due to erroneous print
	int					m_i32CallCount;		// to reach threshold
} STRUCT_MALLOC_SIZE_TRACE;

static STRUCT_MALLOC_SIZE_TRACE	*pstEMALLOCTrace;

static STRUCT_MALLOC_SIZE_TRACE* InitAllocTrace( char *trace_name, int array_size, int print_threshold )
{
	void						*ptr;
	STRUCT_MALLOC_SIZE_TRACE	*pstTrace;

	ptr = kmalloc( (sizeof(STRUCT_MALLOC_SIZE_TRACE) + (array_size * sizeof(STRUCT_ALLOCINFO))), GFP_KERNEL);
	if(NULL == ptr) {
		return (STRUCT_MALLOC_SIZE_TRACE*) NULL;
	}

	pstTrace	= (STRUCT_MALLOC_SIZE_TRACE*) ptr;
	pstTrace->m_pastAllocInfo = ptr + sizeof(STRUCT_MALLOC_SIZE_TRACE);
	pstTrace->m_i32ArraySize	= array_size;
	pstTrace->m_i32NoOfEntriesAdded	= 0;
	strcpy( pstTrace->m_ai8TraceName, trace_name );
	pstTrace->m_i32PrintThres	= print_threshold;
	pstTrace->m_i32CallCount = 0;
	pstTrace->m_i32MaxSizeReceived = 0;

	return pstTrace;
}

static void UpdateAllocSize( STRUCT_MALLOC_SIZE_TRACE	*pstTrace, int i32Size )
{
	STRUCT_ALLOCINFO	*pstAllocInfo;
	int i32Loop;

	if(NULL == pstTrace)
	{
		printk(KERN_ERR "%s %d> NULL RECEIVED\n", __FUNCTION__, __LINE__);
		return;
	}

	// Is it the max alloc size requested?
	if( pstTrace->m_i32MaxSizeReceived < i32Size )
	{
		pstTrace->m_i32MaxSizeReceived = i32Size;
	}

	// Update size info in array
	pstAllocInfo = pstTrace->m_pastAllocInfo;
	for( i32Loop = 0; i32Loop < pstTrace->m_i32NoOfEntriesAdded; ++i32Loop, ++pstAllocInfo )
	{
		if( pstAllocInfo->m_i32Size == i32Size )
		{
			pstAllocInfo->m_i32Count++;
			break;
		}
	}

	// Check and add if it is new entry
	if( i32Loop == pstTrace->m_i32NoOfEntriesAdded )
	{
		// New size
		if( pstTrace->m_i32NoOfEntriesAdded == pstTrace->m_i32ArraySize )
		{
			// No room left for new entry - so print and exit
			printk(KERN_ERR "%s %d> %s No room left for %d", __FUNCTION__, __LINE__, pstTrace->m_ai8TraceName, i32Size);
			return;
		}
		pstAllocInfo->m_i32Size = i32Size;
		pstAllocInfo->m_i32Count = 1;

		// Notify new entry to the world
		++pstTrace->m_i32NoOfEntriesAdded;
		printk(KERN_ERR "%s %d> %s new entry %d", __FUNCTION__, __LINE__, pstTrace->m_ai8TraceName, i32Size);
	}

	// Check whether it is time to print the details
	++pstTrace->m_i32CallCount;
	if( pstTrace->m_i32CallCount == pstTrace->m_i32PrintThres )
	{
		pstAllocInfo = pstTrace->m_pastAllocInfo;
		pstTrace->m_i32CallCount = 0;
		printk(KERN_ERR "%s %d> ### %s Alloc Statistics , max size - %d, emalloc_count - %d\n",
				__FUNCTION__,
				__LINE__,
				pstTrace->m_ai8TraceName,
				pstTrace->m_i32MaxSizeReceived,
				emalloc_count);
		for( i32Loop = 0; i32Loop < pstTrace->m_i32NoOfEntriesAdded; ++i32Loop, ++pstAllocInfo )
		{
			printk(KERN_ERR "#### %d %s s-%d c-%d\n",
					i32Loop,
					pstTrace->m_ai8TraceName,
					pstAllocInfo->m_i32Size,
					pstAllocInfo->m_i32Count);
		}
	}
}
#endif /* yuvaraja.mg - ENABLE_NO_OF_SAME_PACKET_SIZE_COUNT_TRACE */


/* based on printed value received from HostOS_AllocDmaMem of src\host\Clink\Drv\GPL\Common\hostos_linux.c */
static int	static_alloc_offset = (1024 + (4096 * 4));

static int ememinit(u8 *base_addr, u32 init_size)
{
	flag_num = (init_size - static_alloc_offset) / E1000E_PAGE_SIZE;

	printk(KERN_ERR "%s %d>  sizeof(struct skb_shared_info) - %d flag_num - %d\n", __FUNCTION__, __LINE__, sizeof(struct skb_shared_info), flag_num);

#ifndef EM_ATOMIC_CHECK /* gu9gu 20111020 */
	memory_flags = (u8 *)kzalloc(flag_num * sizeof(u8), GFP_KERNEL);
	if(memory_flags == NULL){
		printk(KERN_ERR"memory flags alloc failed");
		return -ENOMEM;
	}
#else
	memory_flags = (atomic_t *)kmalloc(flag_num * sizeof(atomic_t), GFP_KERNEL);
	if(memory_flags == NULL){
		printk(KERN_ERR"memory flags alloc failed");
		return -ENOMEM;
	}
	{
		int i;
		for(i = 0; i < flag_num; i++)
		{
			atomic_set(&memory_flags[i], 1);
		}
	}
#endif

	skb_base_addr = base_addr;
	max_address= (u32)base_addr + init_size;
	return 0;
}

static int e1000e_ioremap(void )
{
	int ret = -1;

#if 0 /* gu9gu 20111020 */
	preempt_disable();
	if (ioremap_init > 0)
	{
		preempt_enable_no_resched();
		return 0;
	}
	ioremap_init=1;
preempt_enable_no_resched();
#else
	if( !atomic_dec_and_test( &initialized ) )
	{
		atomic_inc( &initialized );
		return 0;
	}
#endif

	e1000e_rx_mem_virt_base= (volatile unsigned long)ioremap_cache(E1000E_LIMIT_MEM_BASE,E1000E_LIMIT_MEM_SIZE);
	if (!e1000e_rx_mem_virt_base)
		printk(KERN_INFO "e100e ioremap failed, Abort !!!\n ");
	else
 	{
  		printk(KERN_INFO "e100e ioremap is %lx\n", (unsigned long)e1000e_rx_mem_virt_base);
		ret = 0;
	}
	if (ememinit((u8 *)e1000e_rx_mem_virt_base,E1000E_LIMIT_MEM_SIZE))
		ret = -1;

#ifdef ENABLE_NO_OF_SAME_PACKET_SIZE_COUNT_TRACE /* yuvaraja.mg */
	pstEMALLOCTrace	= InitAllocTrace( "eMalloc", 500, 20000);
#endif /* yuvaraja.mg - ENABLE_NO_OF_SAME_PACKET_SIZE_COUNT_TRACE */

	return ret;
}

static int emalloc_initialized = 0;

static int	emalloc_static_allocated_size = 0;
void* acquire_emalloc_static(int i32Size)
{
	u8				*ret_address;
	unsigned int	ui32Size;

	ui32Size = (unsigned int) i32Size;

	if ( emalloc_initialized == 0 && e1000e_ioremap())
		return NULL;
	else
		emalloc_initialized = 1;

	if( emalloc_static_allocated_size >= static_alloc_offset )
	{
		// we dont have any more static memory
		printk(KERN_ERR "%s %d> - No more static memory for %d (u %d)\n", __FUNCTION__, __LINE__, i32Size, ui32Size );
		return NULL;
	}

	ret_address = skb_base_addr + emalloc_static_allocated_size;

	emalloc_static_allocated_size += ui32Size;
	//printk(KERN_ERR "%s %d> - %d (u %d), 0x%08X\n", __FUNCTION__, __LINE__, i32Size, ui32Size, ret_address);

	return (void*) ret_address;
}
EXPORT_SYMBOL_GPL(acquire_emalloc_static);


void* emalloc(int i32Size)
{
	int i;
#if 1 /* gu9gu 20111024 */
	int j;
#endif
	int flag = 0;
	int free_memory_index;

	u8	*ret_address;
	
	if ( emalloc_initialized == 0 && e1000e_ioremap())
		return NULL;
	else
		emalloc_initialized = 1;

	if( i32Size > E1000E_PAGE_SIZE )
	{
		printk(KERN_ERR "Page size exceeds - %d\n", i32Size);
		return NULL;
	}
	
#ifndef RCU_SPINLOCK_20111021 /* gu9gu 20111020 */
#ifndef EM_ATOMIC_CHECK /* gu9gu 20111021 */
	preempt_disable();
	for (i = 0; i < flag_num; i++ ) {
		if (unlikely(!memory_flags[i]))
		{
			memory_flags[i] = 1;
			free_memory_index = i;
			flag = 1;
			break;
		}
	}
	preempt_enable_no_resched();
#else //EM_ATOMIC_CHECK
#if 0 /* gu9g 20111024 */
	for (i = 0; i < flag_num; i++ ) {
		if (unlikely(atomic_dec_and_test(&memory_flags[i])))
#else
	for (i = 0, j = previous_free_memory_index; i < flag_num; i++ ) {
		if (unlikely(atomic_dec_and_test(&memory_flags[j])))
#endif
		{ /* 1-1=0, assigned */
#if 0 /* gu9gu 20111024 */
			free_memory_index = i;
#else
			free_memory_index = j;
			previous_free_memory_index = j;
#endif
			flag = 1;
			break;
		}
		else
		{
#if 0 /* gu9gu 20111024 */
			atomic_inc(&memory_flags[i]);
#else
			atomic_inc(&memory_flags[j]);
			j = (j+1) % flag_num; 
#endif
		}
	}
#endif //EM_ATOMIC_CHECK

#else
	preempt_disable();
	spin_lock(&memoryflagsmutex);
	for (i = 0; i < flag_num; i++ ) {
//		rcu_read_lock();
		if (!memory_flags[i])
		{
			memory_flags[i] = 1;
//			spin_unlock(&memoryflagsmutex);
			free_memory_index = i;
			flag = 1;
			break;
		}
	}
	spin_unlock(&memoryflagsmutex);
	preempt_enable_no_resched();
#endif

	if(!flag) {
		printk(KERN_ERR"No space left\n");
		return NULL;
	}

	ret_address = &skb_base_addr[free_memory_index*E1000E_PAGE_SIZE];
	ret_address += static_alloc_offset;

#ifdef ENABLE_NO_OF_SAME_PACKET_SIZE_COUNT_TRACE /* yuvaraja.mg */
	UpdateAllocSize(pstEMALLOCTrace, i32Size);
#endif /* yuvaraja.mg - ENABLE_NO_OF_SAME_PACKET_SIZE_COUNT_TRACE */

#ifdef ENABLE_EMALLOC_DEBUG_COUNT_PRINT /* yuvaraja.mg */
	++emalloc_count;
#ifdef DEBUG_ALL_EMALLOC /* yuvaraja.mg */
	if( emalloc_count > ENABLE_EMALLOC_DEBUG_COUNT_PRINT_THRES ) {
		printk(KERN_INFO "emalloc count - %d, 0x%08X\n", emalloc_count, ret_address);
	}
#endif /* yuvaraja.mg - DEBUG_ALL_EMALLOC */
#ifdef DEBUG_MAX_COUNT_ONLY /* yuvaraja.mg */
if( emalloc_count > emalloc_max_count ) {
	emalloc_max_count = emalloc_count;
	printk(KERN_INFO "emalloc max count - %d\n", emalloc_max_count);
}
#endif /* yuvaraja.mg - DEBUG_MAX_COUNT_ONLY */
#endif /* yuvaraja.mg - ENABLE_EMALLOC_DEBUG_COUNT_PRINT */

	return (void *) ret_address;
}

EXPORT_SYMBOL_GPL(emalloc);


void efree(void* to_be_free)
{
	int index;
	if (unlikely(!to_be_free))
		return ;
	
	if (unlikely(( (u32)to_be_free < (u32)skb_base_addr) || ( (u32)to_be_free >= max_address)))
	{
//gu9gu 20111018 kfree(to_be_free);
		printk(KERN_ERR"This should not happen, to_be_free(%lx) is out of range\n", (unsigned long)to_be_free);
		return;
	}
	index = ((u32)to_be_free - (u32)(skb_base_addr + static_alloc_offset))/E1000E_PAGE_SIZE; 

	// check type of buffer to be free
#ifndef RCU_SPINLOCK_20111021 /* gu9gu 20111020 */
#ifndef EM_ATOMIC_CHECK /* gu9gu 20111021 */
//	preempt_disable();
	if(unlikely(!memory_flags[index])) {
//		preempt_enable_no_resched();
		printk(KERN_ERR"you have freed this already \n");
	}
	else
	{
		memory_flags[index] = 0;
//		preempt_enable_no_resched();
	}
#else //EM_ATOMIC_CHECK
	if(likely(atomic_read(&memory_flags[index]) <= 0 )) /* 20111103 multi-thread decrease it minus to value */
		atomic_inc(&memory_flags[index]);
	else
		printk(KERN_ERR"you have freed this(%d) already \n", index);

#endif //EM_ATOMIC_CHECK
#else
	preempt_disable();
	spin_lock(&memoryflagsmutex);
	if(unlikely(!memory_flags[index])) {
		spin_unlock(&memoryflagsmutex);
		preempt_enable_no_resched();
		printk(KERN_ERR"you have freed this already \n");
	}
	else
	{
		memory_flags[index] = 0;
		spin_unlock(&memoryflagsmutex);
		preempt_enable_no_resched();
	}
#endif

#ifdef ENABLE_EMALLOC_DEBUG_COUNT_PRINT /* yuvaraja.mg */
	--emalloc_count;
#ifdef DEBUG_ALL_EMALLOC /* yuvaraja.mg */
	if( emalloc_count >= ENABLE_EMALLOC_DEBUG_COUNT_PRINT_THRES ) {
		printk(KERN_INFO "efree count - %d, 0x%08X\n", emalloc_count, to_be_free);
	}
#endif /* yuvaraja.mg - DEBUG_ALL_EMALLOC */
#endif /* yuvaraja.mg - ENABLE_EMALLOC_DEBUG_COUNT_PRINT */

	return ;
}

EXPORT_SYMBOL_GPL(efree);


 
void* __e_virt_to_phy(volatile void *x) 
{
	return (void *)((u32)(x)- e1000e_rx_mem_virt_base + E1000E_LIMIT_MEM_BASE);
}
EXPORT_SYMBOL_GPL(__e_virt_to_phy);

int is_emalloc_v(volatile unsigned char *vaddr)
{
	if (unlikely(( (u32)vaddr < (u32)skb_base_addr) || ( (u32)vaddr >= max_address)))
		return 0; /* not emalloc virtual address */
	else
		return 1; /* emalloc virtual address */
}
EXPORT_SYMBOL_GPL(is_emalloc_v);

int is_emalloc_p(volatile dma_addr_t address)
{
	if (unlikely(( (u32)address < (u32)E1000E_LIMIT_MEM_BASE) || ( (u32)address >= ((u32)E1000E_LIMIT_MEM_BASE) + (u32)E1000E_LIMIT_MEM_SIZE )))
		return 0; /* not emalloc physical address */
	else
		return 1; /* emalloc physical address */
}
EXPORT_SYMBOL_GPL(is_emalloc_p);



void efreeall(void)
{
	memset(memory_flags, 0, sizeof(u8) * flag_num);
	iounmap((void *)e1000e_rx_mem_virt_base);
}
EXPORT_SYMBOL_GPL(efreeall);


