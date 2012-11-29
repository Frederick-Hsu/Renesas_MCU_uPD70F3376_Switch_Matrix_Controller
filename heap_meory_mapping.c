/**************************************************************************
 * Program name	: heap_memory_mapping.c
 * Description	: Explicitly mapping the heap memory area, indicate the 
 *		: starting address.
 *
 * Author	: XU ZAN
 * Date		: Sun.	Nov. 04, 2012
 * Copyright(C)	 2010 --- 2012	Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 **************************************************************************/


#include "heap_memory_area.h"

/*
 * [Caution]
 *
 * The memory area management functions automatically allocate memory area as necessary from the heap memory area.
 *
 * Also, since the compiler does not automatically allocate this area, when calloc, malloc, or realloc is used, 
 * the heap memory area must be allocated. The area allocation should be performed first by an application.
 *
 *
 *
 * [Heap memory setup example]
 *
 * #define SIZEOF_HEAP 0x1000
 * int __sysheap[SIZEOF_HEAP >> 2];
 * size_t  __sizeof_sysheap = SIZEOF_HEAP;
 *
 *
 *
 * Remarks 
 * 1. The symbol "___sysheap" (three underscores "_") of the variable " _sysheap" (two under-scores "_") points 
 *    to the starting address of heap memory. This value should be a word integer value.
 * 
 * 2. The required heap memory size (bytes) should be set for the variable "__sizeof_sysheap" (two leading 
 *    underscores). If assembly language is used for coding, this value should be set for the 
 *    symbol " ___sizeof_sysheap" (three leading underscores).
 *
 */

int __sysheap[SIZEOF_HEAP>>2] = {0x00000000};
size_t __sizeof_sysheap = SIZEOF_HEAP;

