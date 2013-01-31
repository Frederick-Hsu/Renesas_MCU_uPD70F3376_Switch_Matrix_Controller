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
**  Filename :	serial_user.c
**  Abstract :	This file implements device driver for Serial module.
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

#pragma interrupt INTUD0R MD_INTUD0R
#pragma interrupt INTUD0T MD_INTUD0T
#pragma interrupt INTUD0S MD_INTUD0S
#pragma interrupt INTUD2R MD_INTUD2R
#pragma interrupt INTUD2T MD_INTUD2T
#pragma interrupt INTUD2S MD_INTUD2S
#pragma interrupt INTUD4R MD_INTUD4R
#pragma interrupt INTUD4T MD_INTUD4T
#pragma interrupt INTUD4S MD_INTUD4S
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include "macrodriver.h"
#include "serial.h"
/* Start user code for include definition. Do not edit comment generated here */
/* End user code for include definition. Do not edit comment generated here */
#include "user_define.h"
#include "bus.h"
#include "protocol\Parse_UART2_Message.h"

#include <string.h>

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
extern	volatile UCHAR*	gpUartd0TxAddress;
extern	volatile USHORT	gUartd0TxCnt;
extern	volatile UCHAR*	gpUartd0RxAddress;
extern	volatile USHORT	gUartd0RxCnt;
extern	volatile USHORT	gUartd0RxLen;
extern	volatile UCHAR*	gpUartd2TxAddress;
extern	volatile USHORT	gUartd2TxCnt;
// extern	volatile UCHAR*	gpUartd2RxAddress;
extern UCHAR* gpUartd2RxAddress;	// Modified by XUZAN@2012-11-06


extern	volatile USHORT	gUartd2RxCnt;
// extern	volatile USHORT	gUartd2RxLen;
extern USHORT gUartd2RxLen;

extern	volatile UCHAR*	gpUartd4TxAddress;
extern	volatile USHORT	gUartd4TxCnt;
extern	volatile UCHAR*	gpUartd4RxAddress;
extern	volatile USHORT	gUartd4RxCnt;
extern	volatile USHORT	gUartd4RxLen;
/* Start user code for global definition. Do not edit comment generated here */
/* End user code for global definition. Do not edit comment generated here */

UCHAR sTemp[256] = {0};
int iCnt = 0;

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTUD0R interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__interrupt void MD_INTUD0R(void)
{
	UCHAR	rx_data;

	rx_data = UD0RX;
	if (gUartd0RxLen > gUartd0RxCnt)
	{
		*gpUartd0RxAddress = rx_data;
		gpUartd0RxAddress++;
		gUartd0RxCnt++;
		if (gUartd0RxLen == gUartd0RxCnt)
		{
			UARTD0_ReceiveEndCallback( );
		}
		else
		{
			/* NOT RUN */
		}
	}
	else
	{
		/* NOT RUN */
	}
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTUD0T interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__interrupt void MD_INTUD0T(void)
{
	if (gUartd0TxCnt > 0)
	{
		UD0TX = *gpUartd0TxAddress;
		gpUartd0TxAddress++;
		gUartd0TxCnt--;
	}
	else
	{
		UARTD0_SendEndCallback();
	}
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTUD0S interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__interrupt void MD_INTUD0S(void)
{
	UCHAR	err_type;

	*gpUartd0RxAddress = (UCHAR)UD0RX;
	err_type = (UCHAR)(UD0STR & 0x07);
	UD0STR = (UCHAR)~0x07;
	UARTD0_ErrorCallback( err_type );
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is a callback function of UARTD0.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void UARTD0_ReceiveEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is a callback function of UARTD0.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void UARTD0_SendEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is a callback function of UARTD0.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void UARTD0_ErrorCallback(UCHAR err_type)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}






// START : UART2_MODULE ==========================================================================================================================================
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTUD2R interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__interrupt void MD_INTUD2R(void)
{
	#if 1
		UCHAR	rx_data;	
		

		#if defined (EXPERIEMENT)
		/*
		 * To test the UART data receiving function.
		 * Added by XU ZAN@2012-11-04
		 */
		// int i = 0;
		// UCHAR rxbuf[2048] = {0};	// Added by XUZAN
		
		rx_data = UD2RX;
		sTemp[iCnt] = rx_data;
		iCnt++;
		
		// UARTD2_ReceiveData(rxbuf, 1);	// Added by XUZAN
		
		// gUartd2RxLen = 2;
		#endif	/*    EXPERIEMENT    */
		
		if (gUartd2RxLen > gUartd2RxCnt)
		{
			*gpUartd2RxAddress = rx_data;
			gpUartd2RxAddress++;
			gUartd2RxCnt++;
			
			if (gUartd2RxLen == gUartd2RxCnt)
			{
				UARTD2_ReceiveEndCallback( );
			}
			else
			{
				/* NOT RUN */
			}
		}
		else
		{
		}
	#else
		
		UCHAR sRxBuf[256] = {0};
		USHORT nRxBufLen;
		MD_STATUS Status = MD_OK;
		
		Status = UARTD2_ReceiveData(sRxBuf, 256);
	#endif
	
	UD2RIF = 0;
	UD2RXE = 0;
	UD2RXE = 1;
	
	return;
	
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTUD2T interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__interrupt void MD_INTUD2T(void)
{
	if (gUartd2TxCnt > 0)
	{
		UD2TX = *gpUartd2TxAddress;
		gpUartd2TxAddress++;
		gUartd2TxCnt--;
	}
	else
	{
		UARTD2_SendEndCallback();
	}
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTUD2S interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__interrupt void MD_INTUD2S(void)
{
	UCHAR	err_type;

	*gpUartd2RxAddress = (UCHAR)UD2RX;
	err_type = (UCHAR)(UD2STR & 0x07);
	UD2STR = (UCHAR)~0x07;
	UARTD2_ErrorCallback( err_type );
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is a callback function of UARTD2.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void UARTD2_ReceiveEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	int iResult = -1;
	char *sUART2RxMesg;
	memcpy(sUART2RxMesg, gpUartd2RxAddress, strlen(gpUartd2RxAddress)*sizeof(char));
	iResult = Parse_UART2_Received_Message(sUART2RxMesg);
	/* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is a callback function of UARTD2.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void UARTD2_SendEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is a callback function of UARTD2.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void UARTD2_ErrorCallback(UCHAR err_type)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
// END : UART2_MODULE ==========================================================================================================================================







/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTUD4R interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__multi_interrupt void MD_INTUD4R(void)
{
	UCHAR	rx_data;

	EI();
	rx_data = UD4RX;
	if (gUartd4RxLen > gUartd4RxCnt)
	{
		*gpUartd4RxAddress = rx_data;
		gpUartd4RxAddress++;
		gUartd4RxCnt++;
		if (gUartd4RxLen == gUartd4RxCnt)
		{
			UARTD4_ReceiveEndCallback( );
		}
		else
		{
			/* NOT RUN */
		}
	}
	else
	{
		/* NOT RUN */
	}
	DI();
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTUD4T interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__interrupt void MD_INTUD4T(void)
{
	if (gUartd4TxCnt > 0)
	{
		UD4TX = *gpUartd4TxAddress;
		gpUartd4TxAddress++;
		gUartd4TxCnt--;
	}
	else
	{
		UARTD4_SendEndCallback();
	}
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTUD4S interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__interrupt void MD_INTUD4S(void)
{
	UCHAR	err_type;

	*gpUartd4RxAddress = (UCHAR)UD4RX;
	err_type = (UCHAR)(UD4STR & 0x07);
	UD4STR = (UCHAR)~0x07;
	UARTD4_ErrorCallback( err_type );
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is a callback function of UARTD4.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void UARTD4_ReceiveEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is a callback function of UARTD4.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void UARTD4_SendEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is a callback function of UARTD4.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void UARTD4_ErrorCallback(UCHAR err_type)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */


