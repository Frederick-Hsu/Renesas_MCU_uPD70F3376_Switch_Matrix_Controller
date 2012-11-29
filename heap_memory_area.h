/***********************************************************************************
 * Program anem	: heap_memory_area.h
 * Description	: Clearly indicate the size of heap memory area, because boot code (crte.s)
 *		: does not allocate the heap memory.
 *		: It need programmer to indicate and allocate manually, before the
 *		: user's program running.
 * 		:
 *		: Caution ===> This is globally allocated.
 *		: [Very Important]
 *
 * Author	: XU ZAN
 * Date		: Sun.	Nov. 04, 2012
 * Copyright(C)		2010 --- 2012	Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 ***********************************************************************************/

#ifndef _HEAP_MEMORY_AREA_H
#define _HEAP_MEMORY_AREA_H

	#include <stdio.h>

	#ifndef SIZEOF_HEAP
		/*
		 * Indicates the size of heap memory.
		 * 
		 * Heap memory = 4KByte
		 */
		#define SIZEOF_HEAP	0x1000		
	#endif	/*    SIZEOF_HEAP    */

#endif	/*    _HEAP_MEMORY_AREA_H    */

