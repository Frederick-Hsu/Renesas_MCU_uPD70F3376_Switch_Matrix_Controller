/*
*******************************************************************************
**
**  This device driver was created by Applilet2 for V850ES/Fx3
**  32-Bit Single-Chip Microcontrollers
**
**  Copyright(C) 2002, 2012 Renesas Electronics Corporation
**  All rights reserved by Renesas Electronics Corporation.
**
**  This program should be used on your own responsibility.
**  Renesas Electronics Corporation assumes no responsibility for any losses
**  incurred by customers or third parties arising from the use of this file.
**
**  Filename :	timer.c
**  Abstract :	This file implements device driver for Timer module.
**  APIlib :	Applilet2 for V850ES/Fx3 V2.43 [30 Mar 2011]
**
**  Device :	uPD70F3376
**
**  Compiler :	CA850
**
**  Creation date:	09/26/2012
**  
*******************************************************************************
*/

/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include "macrodriver.h"
#include "timer.h"
/* Start user code for include definition. Do not edit comment generated here */
/* End user code for include definition. Do not edit comment generated here */
#include "user_define.h"

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global definition. Do not edit comment generated here */
/* End user code for global definition. Do not edit comment generated here */


/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function initializes TAA0.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TAA0_Init(void)
{
	TAA0CE = 0;	/* TAA0 operation disable */
	TAA0CCMK0 = 1;	/* INTTAA0CC0 interrupt disable */
	TAA0CCIF0 = 0;	/* clear INTTAA0CC0 interrupt flag */
	TAA0CCMK1 = 1;	/* INTTAA0CC1 interrupt disable */
	TAA0CCIF1 = 0;	/* clear INTTAA0CC1 interrupt flag */
	TAA0OVMK = 1;	/* INTTAA0OV interrupt disable */	
	TAA0OVIF = 0;	/* clear INTTAA0OV interrupt flag */

	/* Set INTTAA0CC0 highest priority */
	TAA0CCIC0 &= 0xF8;

	ISEL20 = 0;	/* selection of TAA0 counter clock = fXP1 */
	/* Interval timer mode setting */
	TAA0CTL0 = TAA_INTERNAL_CLOCK0;
	TAA0CTL1 = TAA_MODE_INTERVAL;
	TAA0CCR0 = TAA0_CCR0_VALUE;
	TAA0CCR1 = 0xffff;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function starts TAA0 counter.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TAA0_Start(void)
{
	TAA0CCIF0 = 0;	/* clear INTTAA0CC0 interrupt flag */
	TAA0CCMK0 = 0;	/* INTTAA0CC0 interrupt enable */
	TAA0CE = 1;	/* TAA0 operation enable */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function stops TAA0 counter.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TAA0_Stop(void)
{
	TAA0CE = 0;	/* TAA0 operation disable */
	TAA0CCMK0 = 1;	/* INTTAA0CC0 interrupt disable */
	TAA0CCIF0 = 0;	/* clear INTTAA0CC0 interrupt flag */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes TAA0 register value.
**
**	Parameters:
**		array_reg :	register value buffer
**		array_num :	register index to be changed
**
**	Returns:
**		MD_OK
**		MD_ARGERROR
**
**-----------------------------------------------------------------------------
*/
MD_STATUS TAA0_ChangeTimerCondition(USHORT* array_reg, UCHAR array_num)
{
	MD_STATUS status = MD_OK;
	if (array_num == 1)
	{
		TAA0CCR0 = array_reg[0];
		status = MD_OK;
	}
	else if (array_num == 2)
	{
		TAA0CCR0 = array_reg[0];
		TAA0CCR1 = array_reg[1];
		status = MD_OK;
	}
	else
	{
		status = MD_ARGERROR;
	}
	
	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function initializes TAA1.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TAA1_Init(void)
{
	TAA1CE = 0;	/* TAA1 operation disable */
	TAA1CCMK0 = 1;	/* INTTAA1CC0 interrupt disable */
	TAA1CCIF0 = 0;	/* clear INTTAA1CC0 interrupt flag */
	TAA1CCMK1 = 1;	/* INTTAA1CC1 interrupt disable */
	TAA1CCIF1 = 0;	/* clear INTTAA1CC1 interrupt flag */
	TAA1OVMK = 1;	/* INTTAA1OV interrupt disable */	
	TAA1OVIF = 0;	/* clear INTTAA1OV interrupt flag */

	/* Set INTTAA1CC0 level 1 priority */
	TAA1CCIC0 &= 0xF8;
	TAA1CCIC0 |= 0x01;

	ISEL21 = 0;	/* selection of TAA1 counter clock = fXP1 */
	/* Interval timer mode setting */
	TAA1CTL0 = TAA_INTERNAL_CLOCK0;
	TAA1CTL1 = TAA_MODE_INTERVAL;
	TAA1CCR0 = TAA1_CCR0_VALUE;
	TAA1CCR1 = 0xffff;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function starts TAA1 counter.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TAA1_Start(void)
{
	TAA1CCIF0 = 0;	/* clear INTTAA1CC0 interrupt flag */
	TAA1CCMK0 = 0;	/* INTTAA1CC0 interrupt enable */
	TAA1CE = 1;	/* TAA1 operation enable */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function stops TAA1 counter.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TAA1_Stop(void)
{
	TAA1CE = 0;	/* TAA1 operation disable */
	TAA1CCMK0 = 1;	/* INTTAA1CC0 interrupt disable */
	TAA1CCIF0 = 0;	/* clear INTTAA1CC0 interrupt flag */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes TAA1 register value.
**
**	Parameters:
**		array_reg :	register value buffer
**		array_num :	register index to be changed
**
**	Returns:
**		MD_OK
**		MD_ARGERROR
**
**-----------------------------------------------------------------------------
*/
MD_STATUS TAA1_ChangeTimerCondition(USHORT* array_reg, UCHAR array_num)
{
	MD_STATUS status = MD_OK;
	if (array_num == 1)
	{
		TAA1CCR0 = array_reg[0];
		status = MD_OK;
	}
	else if (array_num == 2)
	{
		TAA1CCR0 = array_reg[0];
		TAA1CCR1 = array_reg[1];
		status = MD_OK;
	}
	else
	{
		status = MD_ARGERROR;
	}
	
	return (status);
}

/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */


