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
**  Filename :	 main.c
**  Abstract :	This file implements main function.
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

#include "JTAG_On_Chip_Debug_Mode.h"
#include "Project.h"

#include "bus.h"
#include "ADC_and_DAC.h"


/*========================================================*/
#include "Just_test_and_debug.h"
/*========================================================*/

#pragma ioreg


/******************************************************************************/
// Macros :
#if !defined (ENABLE_OCDM_DEBUG)
	#define ENABLE_OCDM_DEBUG
	// #undef	ENABLE_OCDM_DEBUG
#endif

#define ADC_DEBUG
unsigned char rxbuf[32] = {0};	
/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global definition. Do not edit comment generated here */
/* End user code for global definition. Do not edit comment generated here */



void  main(void)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function implements main function.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
{
	long i = 0, j = 0;
	//UCHAR rxbuf[256] = {0};	

	SystemInit();
	
	#if defined (ENABLE_OCDM_DEBUG)
		Enable_OCDM();
	#else
		Disable_OCDM();
	#endif	
	
	#if defined (TEST_DEBUG_PURPOSE)
		SetInitialState_TurnOffAllSwitches();
	#endif	/* End   TEST_DEBUG_PURPOSE    */
	
	UARTD2_Start();		// Open the COM port, communicating with PC.

	UARTD2_ReceiveData(rxbuf,256);	
	
	for (i=0; i<5000000; i++)
	{
		NOP();
	}
	Display_SW_Version();
	for (i=0; i<5000000; i++)
	{
		NOP();
	}
		
	Test_Switch_Ctrl();
	// Enable_All_Switches();
	
	

	
	/* Start user code. Do not edit comment generated here */
	while (1) 
	{
		#if defined (TEST_DEBUG_PURPOSE)
			// Test_MCU_Chip_System();
			// Print_ADC_Values_8Channels();
		#endif	/* End   TEST_DEBUG_PURPOSE    */
		
		for (i=0; i<5000000; i++)
		{
			NOP();
		}
	}
	/* End user code. Do not edit comment generated here */
}


/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */


