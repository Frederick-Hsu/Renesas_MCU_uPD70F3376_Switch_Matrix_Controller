/******************************************************************************************
 * Program name	: JTAG_On_Chip_Debug_Mode.c
 * Description	: Do some settings for the JTAG On-Chip-Debug module. Implementations
 * Author	: XU ZAN
 * Date		: Tue.	July 24, 2012
 * Copyright(C)		2010 --- 2012	Hella (Shanghai) Electronics Co., Ltd
 * All rights reserved.
 *
 ******************************************************************************************/

#include "JTAG_On_Chip_Debug_Mode.h"

#pragma ioreg


/*
 * OCDM : On-Chip-debug mode register
 * The 8-bit OCDM register specifies whether dedicated pins of the microcontroller operates in normal operation mode
 * or can be used for on-chip debugging. 
 * To make these pins available for on-chip debugging, bit OCDM.OCDM0 must be set while pin /DRST is high. If the on-chip
 * debug mode is selected, the corresponding pins are automatically set as input or outputpins, respectively.
 *
 *	OCDM bits :
 *
 *	  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 *	-----+-----+-----+-----+-----+-----+-----+-----|
 *	  0  |  0  |  0  |  0  |  0  |  0  |  0  |OCDM0|
 *	-----------------------------------------------+
 *
 *	Enables / disables the JTAG debugging interface :
 *	----------------+-------+-------------------------------
 *			|   0	| Pins are used in normal 
 *			|	| operation mode.
 *	       OCDM0	+-------+-------------------------------
 *			|   1	| Pins are used in on-chip
 *			|	| debug mode.
 *	----------------+-------+-------------------------------
 * 
 */

void Enable_OCDM(void)
{
	/*
	 * Set the bit0 of OCDM : OCDM0 to 1, 
	 * enable the debug mode.
	 */
	OCDM |= 0x01;
}

void Disable_OCDM(void)
{
	/*
	 * Set the bit0 of OCDM : OCDM0 to 0,
	 * disable the debug mode.
	 */
	OCDM &= 0xFE;
}

