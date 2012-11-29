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
**  Filename :	systeminit.c
**  Abstract :	This file implements system initializing function.
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
#include "serial.h"
#include "can.h"
#include "port.h"
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

extern unsigned long _S_romp;

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function  initializes each macro.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void  SystemInit(void)
{
	_rcopy(&_S_romp, -1);	
	E00 = 0;	/* disable dma0 - dma3 */
	E11 = 0;
	E22 = 0;
	E33 = 0;	
	DI();	/* disable interrupt */
	/*Process of reset*/
	CG_ReadResetSource();
	/*Initializes the I/O ports*/
	PORT_Init();
	
	/*Initializes UARTD channel 0	*/
	UARTD0_Init();
	
	
	/*Initializes UARTD channel 2*/
	/*
	 * Notice : UART2 COM port is dedicatedly used to communicate with PC.
	 * Remarked by XU ZAN @2012-07-27
	 */
	UARTD2_Init();
	
	
	
	/*Initializes UARTD channel 4*/
	UARTD4_Init();
	/*Initializes CAN0*/
	CAN0_Init();
	/*Initializes TAA0*/
	TAA0_Init();
	/*Initializes TAA1*/
	TAA1_Init();
	/* PCL setting */
	PCLM = CG_PCL_DISABLE;
	
	EI();	/* enable interrupt */
}

/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */


