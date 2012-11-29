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
**  Filename :	can_user.c
**  Abstract :	This file implements device driver for CAN module.
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

#pragma interrupt INTC0WUP MD_INTC0WUP
#pragma interrupt INTC0REC MD_INTC0REC
#pragma interrupt INTC0TRX MD_INTC0TRX
#pragma interrupt INTC0ERR MD_INTC0ERR
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include "macrodriver.h"
#include "can.h"
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
**		This function is INTC0WUP interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__interrupt void MD_INTC0WUP(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTC0TRX interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__interrupt void MD_INTC0TRX(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTC0REC interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__interrupt void MD_INTC0REC(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTC0ERR interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__interrupt void MD_INTC0ERR(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */


