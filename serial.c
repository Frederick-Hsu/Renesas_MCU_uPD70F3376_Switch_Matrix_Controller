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
**  Filename :	serial.c
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

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
volatile UCHAR*	gpUartd0TxAddress;	/* uartd0 transmit buffer address */
volatile USHORT	gUartd0TxCnt;	/* uartd0 transmit data number */
volatile UCHAR*	gpUartd0RxAddress;	/* uartd0 receive buffer address */
volatile USHORT	gUartd0RxCnt;	/* uartd0 receive data number */
// volatile USHORT	gUartd0RxLen = 2;	/* uartd0 receive data length */
USHORT	gUartd0RxLen = 2;
volatile UCHAR*	gpUartd2TxAddress;	/* uartd2 transmit buffer address */
volatile USHORT	gUartd2TxCnt;	/* uartd2 transmit data number */
volatile UCHAR*	gpUartd2RxAddress;	/* uartd2 receive buffer address */
//UCHAR*	gpUartd2RxAddress;
volatile USHORT	gUartd2RxCnt;	/* uartd2 receive data number */
volatile USHORT	gUartd2RxLen;	/* uartd2 receive data length */
volatile UCHAR*	gpUartd4TxAddress;	/* uartd4 transmit buffer address */
volatile USHORT	gUartd4TxCnt;	/* uartd4 transmit data number */
volatile UCHAR*	gpUartd4RxAddress;	/* uartd4 receive buffer address */
volatile USHORT	gUartd4RxCnt;	/* uartd4 receive data number */
volatile USHORT	gUartd4RxLen;	/* uartd4 receive data length */
/* Start user code for global definition. Do not edit comment generated here */
/* End user code for global definition. Do not edit comment generated here */



void UARTD0_Init(void)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function initializes UARTD0.
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
	UD0TXE = 0;	/* disable transmission operation(uartd0) */
	UD0RXE = 0;	/* disable reception operation(uartd0) */
	UD0PWR = 0;	/* disable UARTD0 operation */
	UD0TMK = 1;	/* INTUD0T interrupt disable */
	UD0TIF = 0;	/* clear INTUD0T interrupt flag */
	UD0RMK = 1;	/* INTUD0R interrupt disable */
	UD0RIF = 0;	/* clear INTUD0R interrupt flag */
	UD0SMK = 1;	/* INTUD0S interrupt disable */
	UD0SIF = 0;	/* clear INTUD0S interrupt flag */
	/* Set INTUD0R level 1 priority */
	UD0RIC &= 0xF8;
	UD0RIC |= 0x01;
	/* Set INTUD0S lowest priority */
	UD0SIC |= 0x07;
	/* Set INTUD0T lowest priority */
	UD0TIC |= 0x07;
	UD0CTL1 = UARTD_BASECLK_FXP1_16;
	UD0CTL2 = UARTD0_BASECLK_DIVISION;
	ISEL26 = 0;	/* selection of UARTD0 counter clock = fXP1 */
	UD0CTL0 = UARTD_TRANSFDIR_LSB | UARTD_PARITY_NONE | UARTD_DATALENGTH_8BIT | UARTD_STOPLENGTH_1BIT;
	/* UARTD0 TXDD0 pin set */
	PMC3L |= 0x01;
	/* UARTD0 RXDD0 pin set */
	PMC3L |= 0x02;
}


void UARTD0_Start(void)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function starts the UARTD0 operation.
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
	UD0TIF = 0;	/* clear INTUD0T interrupt flag */
	UD0TMK = 0;	/* INTUD0T interrupt enable */
	UD0RIF = 0;	/* clear INTUD0R interrupt flag */
	UD0RMK = 0;	/* INTUD0R interrupt enable */
	UD0SIF = 0;	/* clear INTUD0S interrupt flag */
	UD0SMK = 0;	/* INTUD0S interrupt enable */
 
	UD0PWR = 1;	/* enable UARTD0 operation */
	UD0TXE = 1;	/* enable transmission operation(uartd0) */
	UD0RXE = 1;	/* enable reception operation(uartd0) */
}


void UARTD0_Stop(void)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function stops the UARTD0 operation.
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
	UD0TXE = 0;	/* disable transmission operation(uartd0) */
	UD0RXE = 0;	/* disable reception operation(uartd0) */
	UD0PWR = 0;	/* disable UARTD0 operation */
	UD0TMK = 1;	/* INTUD0T interrupt disable */
	UD0TIF = 0;	/* clear INTUD0T interrupt flag */
	UD0RMK = 1;	/* INTUD0R interrupt disable */
	UD0RIF = 0;	/* clear INTUD0R interrupt flag */
	UD0SMK = 1;	/* INTUD0S interrupt disable */
	UD0SIF = 0;	/* clear INTUD0S interrupt flag */
}


MD_STATUS UARTD0_ReceiveData(UCHAR* rxbuf, USHORT rxnum)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function receives UARTD0 data.
**
**	Parameters:
**		rxbuf :	receive buffer pointer
**		rxnum :	buffer size
**
**	Returns:
**		MD_OK
**		MD_ARGERROR
**
**-----------------------------------------------------------------------------
*/
{
	MD_STATUS status = MD_OK;
	
	if (rxnum < 1)
	{
		status = MD_ARGERROR;
	}
	else
	{
		gUartd0RxCnt = 0;
		gUartd0RxLen = rxnum;
		gpUartd0RxAddress = rxbuf;
		status = MD_OK;
	}
	
	return (status);
}


MD_STATUS UARTD0_SendData(UCHAR* txbuf, USHORT txnum)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function sends UARTD0 data.
**
**	Parameters:
**		txbuf :	transfer buffer pointer
**		txnum :	buffer size
**
**	Returns:
**		MD_OK
**		MD_ARGERROR
**		MD_DATAEXISTS
**
**-----------------------------------------------------------------------------
*/
{
	MD_STATUS status = MD_OK;
	
	if (txnum < 1)
	{
		status = MD_ARGERROR;
	}
	else
	{
		gpUartd0TxAddress = txbuf;
		gUartd0TxCnt = txnum;	
		if((UD0STR & 0x80) == 0)
		{
			UD0TMK = 1;	/* INTUD0T interrupt disable */
			UD0TX = *gpUartd0TxAddress;
			gpUartd0TxAddress++;
			gUartd0TxCnt--;
			UD0TMK = 0;	/* INTUD0T interrupt enable */
			status = MD_OK;
		}
		else
		{
			status = MD_DATAEXISTS;
		}
	}
	
	return (status);
}






// START : UART2_MODULE ==========================================================================================================================================
/*
 * This UART2 is used to communicate with PC.
 * 
 * Remarked by XU ZAN @2012-07-26
 */
void UARTD2_Init(void)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function initializes UARTD2.
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
	UD2TXE = 0;	/* disable transmission operation(uartd2) */
	UD2RXE = 0;	/* disable reception operation(uartd2) */
	UD2PWR = 0;	/* disable UARTD2 operation */
	UD2TMK = 1;	/* INTUD2T interrupt disable */
	UD2TIF = 0;	/* clear INTUD2T interrupt flag */
	UD2RMK = 1;	/* INTUD2R interrupt disable */
	UD2RIF = 0;	/* clear INTUD2R interrupt flag */
	UD2SMK = 1;	/* INTUD2S interrupt disable */
	UD2SIF = 0;	/* clear INTUD2S interrupt flag */
	/* Set INTUD2R level 1 priority */
	UD2RIC &= 0xF8;
	UD2RIC |= 0x01;
	/* Set INTUD2S lowest priority */
	UD2SIC |= 0x07;
	/* Set INTUD2T lowest priority */
	UD2TIC |= 0x07;
	UD2CTL1 = UARTD_BASECLK_FXP1_32;
	UD2CTL2 = UARTD2_BASECLK_DIVISION;
	ISEL32 = 0;	/* selection of UARTD2 counter clock = fXP1 */
	UD2CTL0 = UARTD_TRANSFDIR_LSB | UARTD_PARITY_NONE | UARTD_DATALENGTH_8BIT | UARTD_STOPLENGTH_1BIT;
	/* UARTD2 TXDD2 pin set */
	PMC3H |= 0x01;
	/* UARTD2 RXDD2 pin set */
	PMC3H |= 0x02;
}


void UARTD2_Start(void)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function starts the UARTD2 operation.
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
	UD2TIF = 0;	/* clear INTUD2T interrupt flag */
	UD2TMK = 0;	/* INTUD2T interrupt enable */
	UD2RIF = 0;	/* clear INTUD2R interrupt flag */
	UD2RMK = 0;	/* INTUD2R interrupt enable */
	UD2SIF = 0;	/* clear INTUD2S interrupt flag */
	UD2SMK = 0;	/* INTUD2S interrupt enable */
 
	UD2PWR = 1;	/* enable UARTD2 operation */
	UD2TXE = 1;	/* enable transmission operation(uartd2) */
	UD2RXE = 1;	/* enable reception operation(uartd2) */
}


void UARTD2_Stop(void)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function stops the UARTD2 operation.
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
	UD2TXE = 0;	/* disable transmission operation(uartd2) */
	UD2RXE = 0;	/* disable reception operation(uartd2) */
	UD2PWR = 0;	/* disable UARTD2 operation */
	UD2TMK = 1;	/* INTUD2T interrupt disable */
	UD2TIF = 0;	/* clear INTUD2T interrupt flag */
	UD2RMK = 1;	/* INTUD2R interrupt disable */
	UD2RIF = 0;	/* clear INTUD2R interrupt flag */
	UD2SMK = 1;	/* INTUD2S interrupt disable */
	UD2SIF = 0;	/* clear INTUD2S interrupt flag */
}


MD_STATUS UARTD2_ReceiveData(UCHAR* rxbuf, USHORT rxnum)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function receives UARTD2 data.
**
**	Parameters:
**		rxbuf :	receive buffer pointer
**		rxnum :	buffer size
**
**	Returns:
**		MD_OK
**		MD_ARGERROR
**
**-----------------------------------------------------------------------------
*/
{
	MD_STATUS status = MD_OK;
	unsigned int i = 0;
	
	#if 1
		if (rxnum < 1)
		{
			status = MD_ARGERROR;
		}
		else
		{
			gUartd2RxCnt = 0;
			gUartd2RxLen = rxnum;
			gpUartd2RxAddress = rxbuf;
			status = MD_OK;
		}
	#else	
		for (i=0; i<rxnum; i++)
		{
			if ( (UD2STR & 0x07) != 0x00 )
			{
				/*
				 * Set the Rx error flag.
				 */
				UD2STR &= 0xF8;
				status = MD_ARGERROR;
			}
			else
			{
				rxbuf[i] = UD2RX;
			}
		}
	#endif
	
	return (status);
}


MD_STATUS UARTD2_SendData(UCHAR* txbuf, USHORT txnum)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function sends UARTD2 data.
**
**	Parameters:
**		txbuf :	transfer buffer pointer
**		txnum :	buffer size
**
**	Returns:
**		MD_OK
**		MD_ARGERROR
**		MD_DATAEXISTS
**
**-----------------------------------------------------------------------------
*/
{
	MD_STATUS status = MD_OK;
	
	if (txnum < 1)
	{
		status = MD_ARGERROR;
	}
	else
	{
		gpUartd2TxAddress = txbuf;
		gUartd2TxCnt = txnum;	
		if((UD2STR & 0x80) == 0)
		{
			UD2TMK = 1;	/* INTUD2T interrupt disable */
			UD2TX = *gpUartd2TxAddress;
			gpUartd2TxAddress++;
			gUartd2TxCnt--;
			UD2TMK = 0;	/* INTUD2T interrupt enable */
			status = MD_OK;
		}
		else
		{
			status = MD_DATAEXISTS;
		}
	}
	
	return (status);
}
// END : UART2_MODULE ==========================================================================================================================================









void UARTD4_Init(void)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function initializes UARTD4.
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
	UD4TXE = 0;	/* disable transmission operation(uartd4) */
	UD4RXE = 0;	/* disable reception operation(uartd4) */
	UD4PWR = 0;	/* disable UARTD4 operation */
	UD4TMK = 1;	/* INTUD4T interrupt disable */
	UD4TIF = 0;	/* clear INTUD4T interrupt flag */
	UD4RMK = 1;	/* INTUD4R interrupt disable */
	UD4RIF = 0;	/* clear INTUD4R interrupt flag */
	UD4SMK = 1;	/* INTUD4S interrupt disable */
	UD4SIF = 0;	/* clear INTUD4S interrupt flag */
	/* Set INTUD4R level 2 priority */
	UD4RIC &= 0xF8;
	UD4RIC |= 0x02;
	/* Set INTUD4S lowest priority */
	UD4SIC |= 0x07;
	/* Set INTUD4T lowest priority */
	UD4TIC |= 0x07;
	UD4CTL1 = UARTD_BASECLK_FXP1_32;
	UD4CTL2 = UARTD4_BASECLK_DIVISION;
	ISEL34 = 0;	/* selection of UARTD4 counter clock = fXP1 */
	UD4CTL0 = UARTD_TRANSFDIR_LSB | UARTD_PARITY_NONE | UARTD_DATALENGTH_8BIT | UARTD_STOPLENGTH_1BIT;
	/* UARTD4 TXDD4 pin set */
	PFC9H |= 0x80;
	PFCE9H |= 0x80;
	PMC9H |= 0x80;
	/* UARTD4 RXDD4 pin set */
	PFC9H |= 0x40;
	PFCE9H |= 0x40;
	PMC9H |= 0x40;
}


void UARTD4_Start(void)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function starts the UARTD4 operation.
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
	UD4TIF = 0;	/* clear INTUD4T interrupt flag */
	UD4TMK = 0;	/* INTUD4T interrupt enable */
	UD4RIF = 0;	/* clear INTUD4R interrupt flag */
	UD4RMK = 0;	/* INTUD4R interrupt enable */
	UD4SIF = 0;	/* clear INTUD4S interrupt flag */
	UD4SMK = 0;	/* INTUD4S interrupt enable */
 
	UD4PWR = 1;	/* enable UARTD4 operation */
	UD4TXE = 1;	/* enable transmission operation(uartd4) */
	UD4RXE = 1;	/* enable reception operation(uartd4) */
}


void UARTD4_Stop(void)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function stops the UARTD4 operation.
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
	UD4TXE = 0;	/* disable transmission operation(uartd4) */
	UD4RXE = 0;	/* disable reception operation(uartd4) */
	UD4PWR = 0;	/* disable UARTD4 operation */
	UD4TMK = 1;	/* INTUD4T interrupt disable */
	UD4TIF = 0;	/* clear INTUD4T interrupt flag */
	UD4RMK = 1;	/* INTUD4R interrupt disable */
	UD4RIF = 0;	/* clear INTUD4R interrupt flag */
	UD4SMK = 1;	/* INTUD4S interrupt disable */
	UD4SIF = 0;	/* clear INTUD4S interrupt flag */
}


MD_STATUS UARTD4_ReceiveData(UCHAR* rxbuf, USHORT rxnum)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function receives UARTD4 data.
**
**	Parameters:
**		rxbuf :	receive buffer pointer
**		rxnum :	buffer size
**
**	Returns:
**		MD_OK
**		MD_ARGERROR
**
**-----------------------------------------------------------------------------
*/
{
	MD_STATUS status = MD_OK;
	
	if (rxnum < 1)
	{
		status = MD_ARGERROR;
	}
	else
	{
		gUartd4RxCnt = 0;
		gUartd4RxLen = rxnum;
		gpUartd4RxAddress = rxbuf;
		status = MD_OK;
	}
	
	return (status);
}


MD_STATUS UARTD4_SendData(UCHAR* txbuf, USHORT txnum)
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function sends UARTD4 data.
**
**	Parameters:
**		txbuf :	transfer buffer pointer
**		txnum :	buffer size
**
**	Returns:
**		MD_OK
**		MD_ARGERROR
**		MD_DATAEXISTS
**
**-----------------------------------------------------------------------------
*/
{
	MD_STATUS status = MD_OK;
	
	if (txnum < 1)
	{
		status = MD_ARGERROR;
	}
	else
	{
		gpUartd4TxAddress = txbuf;
		gUartd4TxCnt = txnum;	
		if((UD4STR & 0x80) == 0)
		{
			UD4TMK = 1;	/* INTUD4T interrupt disable */
			UD4TX = *gpUartd4TxAddress;
			gpUartd4TxAddress++;
			gUartd4TxCnt--;
			UD4TMK = 0;	/* INTUD4T interrupt enable */
			status = MD_OK;
		}
		else
		{
			status = MD_DATAEXISTS;
		}
	}
	
	return (status);
}

/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */


