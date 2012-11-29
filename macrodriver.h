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
**  Filename :	macrodriver.h
**  Abstract :	This file implements general head file.
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
#ifndef _MDSTATUS_
#define _MDSTATUS_
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#pragma ioreg		/* enable use the register directly in ca850 compiler */
/*
*******************************************************************************
**	Register bit define
*******************************************************************************
*/

/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
#define	EI()	__asm("ei")
#define	DI()	__asm("di")
#define	NOP()	__asm("nop")
#define	HALT()	__asm("halt")

/* Data type defintion */
typedef	unsigned long	ULONG;
typedef	signed long	SLONG;

typedef	unsigned int	UINT;
typedef UINT		DWORD;	// 32-bit	// Added by XUZAN @2012-10-05
typedef	signed int	SINT;

typedef	unsigned short	USHORT;
typedef	signed short	SHORT;
typedef USHORT		WORD;	// 16-bit	// Added by XUZAN @2012-10-05

typedef	unsigned char	UCHAR;
typedef UCHAR		BYTE;	// 8-bit	// Added by XUZAN @2012-10-05
typedef	signed char	SCHAR;

typedef	unsigned char	BOOL;
typedef	unsigned short	MD_STATUS;

#define	MD_ON		1
#define	MD_OFF		0

#define	MD_TRUE		1
#define	MD_FALSE	0


/*
 * Define the Port INPUT/OUTPUT state : LEVEL
 * Added by XUZAN @2012-10-05
 */
enum LEVEL
{
	LOW 	= 0,
	HIGH 	= 1
};


/* Status list definition */
#define	MD_STATUSBASE		0x00
#define	MD_OK				(MD_STATUSBASE + 0x0)	/* register setting OK */
#define	MD_RESET			(MD_STATUSBASE + 0x1)	/* reset input */
#define	MD_SENDCOMPLETE		(MD_STATUSBASE + 0x2)	/* send data complete */
#define	MD_ADDRESSMATCH		(MD_STATUSBASE + 0x3)	/* IIC slave address match */
#define	MD_OVF				(MD_STATUSBASE + 0x4)	/* timer count overflow */
#define	MD_SPT				(MD_STATUSBASE + 0x7)	/* IIC stop */
#define	MD_NACK				(MD_STATUSBASE + 0x8)	/* IIC no ACK */
#define	MD_SLAVE_SEND_END	(MD_STATUSBASE + 0x9)	/* IIC slave send end */
#define	MD_SLAVE_RCV_END	(MD_STATUSBASE + 0x0A)	/* IIC slave receive end */
#define	MD_MASTER_SEND_END	(MD_STATUSBASE + 0x0B)	/* IIC master send end */
#define	MD_MASTER_RCV_END	(MD_STATUSBASE + 0x0C)	/* IIC master receive end */
#define	MD_UNDEREXEC		(MD_STATUSBASE + 0x0D)	/* DMA transfer under execute */
#define	MD_COMPLETED		(MD_STATUSBASE + 0x0E)	/* DMA transfer completed */

/* Error list definition */
#define	MD_ERRORBASE		0x80
#define	MD_ERROR			(MD_ERRORBASE + 0x0)	/* error */
#define	MD_RESOURCEERROR	(MD_ERRORBASE + 0x1)	/* no resource available */
#define	MD_PARITYERROR		(MD_ERRORBASE + 0x2)	/* UARTn parity error n=0,1,2 */
#define	MD_OVERRUNERROR		(MD_ERRORBASE + 0x3)	/* UARTn overrun error n=0,1,2 */
#define	MD_FRAMEERROR		(MD_ERRORBASE + 0x4)	/* UARTn frame error n=0,1,2 */
#define	MD_ARGERROR			(MD_ERRORBASE + 0x5)	/* Error agrument input error */
#define	MD_TIMINGERROR		(MD_ERRORBASE + 0x6)	/* Error timing operation error */
#define	MD_SETPROHIBITED	(MD_ERRORBASE + 0x7)	/* setting prohibited */
#define	MD_ODDBUF			(MD_ERRORBASE + 0x8)	/* in 16bit transfer mode,buffer size should be even */
#define	MD_DATAEXISTS		(MD_ERRORBASE + 0x9)	/* Data to be transferred next exists in TXBn register */
#define	MD_STSERROR			(MD_ERRORBASE + 0x0A)	/* CAN status error */
#define	MD_ALRDYSTART		(MD_ERRORBASE + 0x0B)	/* CAN-controller is already started error */
#define	MD_NOMSG			(MD_ERRORBASE + 0x0C)	/* CAN message not received */
#define	MD_BUSY				(MD_ERRORBASE + 0x0D)	/* busy */


/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
#endif
