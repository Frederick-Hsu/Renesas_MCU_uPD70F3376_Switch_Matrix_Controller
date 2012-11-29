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
**  Filename :	system.c
**  Abstract :	This file implements device driver for System module.
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
#include "system.h"
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
**		This function initializes the clock generator.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void Clock_Init(void)
{
	UCHAR psval = 0;

	/* Set main system clock */
	OSTS = CG_OSCSTAB_SEL16;
	psval = CG_CPUCLK_MAINFEEDBACK | CG_CPUCLK_SUBNOTFEED | CG_CPUCLK_MAINENABLE;
	PRCMD = psval;
	PCC = psval;
	while (!OSTC)
	{
		;
	}
	PLLS = CG_PCL_DISABLE;
	PLLON = 1;
	while (LOCKR)
	{
		;
	}
	psval = CG_MAINSYS_MAINOSC;
	PRCMD = psval;
	MCM = psval;
	SELPLL = 1;
	/* Set fCPU */
	psval = PCC | CG_CPUCLK_MAIN0;
	PRCMD = psval;
	PCC = psval;
	RCM = CG_RCM_INITIALVALUE | CG_LOWCLK_OPER | CG_HICLK_OPER;
	/* Set fXP1 */
	SELCNT4 = CG_SELCNT4_FXX;
	/* Set fBRG */
	PRSM0 = CG_PRESCALER3_DISABLE;
	/* Stand-by setting */
	psval = CG_STANDBY_INTWDT2EN | CG_STANDBY_NMIEN | CG_STANDBY_MSKIEN;
	PRCMD = psval;
	PSC = psval;
	/* WDT2 setting */
	WDTM2 = 0x1F;
}

/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */


