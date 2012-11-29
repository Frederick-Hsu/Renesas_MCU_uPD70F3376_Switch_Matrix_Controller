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
**  Filename :	can.c
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

const CAN_RegBaseAddr	gcCanRegBaseAddr[CAN_NUM_OF_CH] = {
	/* Channel 0 */
	{
		/* CAN global register */
		(CAN_GlbRegType *)(CAN_STP_PIO_CAN_BASE_ADDR + 0x0),
		/* CAN module register */
		(CAN_ChRegType *)(CAN_STP_PIO_CAN_BASE_ADDR + 0x40),
		/* CAN message buffer */
		(CAN_MsgRegType *)(CAN_STP_PIO_CAN_BASE_ADDR + 0x100)
	},
	/* Channel 1 */
	{
		/* CAN global register */
		(CAN_GlbRegType *)(CAN_STP_PIO_CAN_BASE_ADDR + 0x600),
		/* CAN module register */
		(CAN_ChRegType *)(CAN_STP_PIO_CAN_BASE_ADDR + 0x640),
		/* CAN message buffer */
		(CAN_MsgRegType *)(CAN_STP_PIO_CAN_BASE_ADDR + 0x700)
	}
};

/*
 *		CAN global information
 */
 /* Information of CAN macro (Global) */
const UCHAR		gcCanGlbIniMacro[CAN_NUM_OF_CH] = {
	/* Channel 0 */
	0x06,
	/* Channel 1 */
	0x00
};
/*
 *		CAN module information
 */
/* Information of using CAN channel */
const UCHAR		gcCanChIniUse[CAN_NUM_OF_CH] = {
	/*
	 * Channel 0
	 *- Channel  use
	 *- CAN message buffer management number = 0
	 */
	CAN_INICH_USE | 0,
	/*
	 * Channel 1
	 *- Channel  no use
	 */
	0
};

/* Total number of using CAN channel */
#define	CAN_NUM_OF_USED_CH		1

/* Information of CAN module interrupt */
const USHORT	gcCanChIniInt[CAN_NUM_OF_USED_CH] = {
	/* Channel 0 */
	CAN_INICH_INT_SET_WAKUP |	\
	CAN_INICH_INT_SET_ARBLST |	\
	CAN_INICH_INT_CLR_PRTERR |	\
	CAN_INICH_INT_SET_ERRSTS |	\
	CAN_INICH_INT_SET_RX |	\
	CAN_INICH_INT_SET_TX
};

/* Information of CAN macro (Module) */
const UCHAR		gcCanChIniMacro[CAN_NUM_OF_USED_CH] = {
	/* Channel 0 */
	0x00
};

/* Information of baud rate setting */
const CAN_ChBpsInf		gcCanChIniBps[CAN_NUM_OF_USED_CH] = {
	/* Channel 0 */
	{
		/* CnGMCS */
		0x00,
		/* CnBRP */
		0x01,
		/* CnBTR */
		0x330A
	}
};
/* Information of mask setting */
#define	CAN_NUM_OF_MASK		(4)

const ULONG		gcCanChIniMask[CAN_NUM_OF_USED_CH][CAN_NUM_OF_MASK] = {
	/* Channel 0 */
	{
		/* Mask1 */
		0x1FFFFFFF,
		/* Mask2 */
		0x1FFFFFFF,
		/* Mask3 */
		0x1FFFFFFF,
		/* Mask4 */
		0x1FFFFFFF
	}
};
/* Start number of management CAN message buffer No (each channel) */
const UCHAR		gcCanChDrvBufNoTop[CAN_NUM_OF_USED_CH] = {
	/* Channel 0 */
	0
};

/* Management number of CAN message buffer (each channel) */
const UCHAR		gcCanChDrvBufNoSize[CAN_NUM_OF_USED_CH] = {
	/* Channel 0 */
	3
};

/* Total number of CAN message buffer (each channel) */
const UCHAR		gcCanChNumOfCanBuf[CAN_NUM_OF_USED_CH] = {
	/* Channel 0 */
	32
};

/*
 *		CAN message buffer information
 */

/* Total number of using CAN message buffer */
#define	CAN_NUM_OF_DRVBUF	3

/* Information of CAN message buffer initial attribute1(Send/Receive, Frame type, overwrite) */
const UCHAR		gcCanBufIniAtr1[CAN_NUM_OF_DRVBUF] = {
	/*- CAN message buffer management number = 0 */
	CAN_INIMSG_ADDRTYP_USE | CAN_INIMSG_MSGTYP_TX | CAN_INIMSG_FRMTYP_DAT,
	/*- CAN message buffer management number = 1 */
	CAN_INIMSG_ADDRTYP_USE | CAN_INIMSG_MSGTYP_RX | CAN_INIMSG_FRMTYP_DAT | CAN_INIMSG_OVRWRT,
	/*- CAN message buffer management number = 2 */
	CAN_INIMSG_ADDRTYP_USE | CAN_INIMSG_MSGTYP_RX | CAN_INIMSG_FRMTYP_DAT | CAN_INIMSG_OVRWRT
};

/* Information of CAN message buffer initial attribute2(DLC, CAN channel No., Interrupt) */
const UCHAR		gcCanBufIniAtr2[CAN_NUM_OF_DRVBUF] = {
	/*- CAN message buffer management number = 0 */
	0x08 | 0x00,
	/*- CAN message buffer management number = 1 */
	0x00 | 0x00 | CAN_INIMSG_IE,
	/*- CAN message buffer management number = 2 */
	0x00 | 0x00
};

/* Information of CAN message buffer number */
const UCHAR		gcCanBufIniBufno[CAN_NUM_OF_DRVBUF] = {
/* Channel 0 */
	/*- CAN message buffer management number = 0 */
	17,
	/*- CAN message buffer management number = 1 */
	8,
	/*- CAN message buffer management number = 2 */
	31
};

/* Information of CAN-ID setting */
const ULONG		gcCanBufIniCanId[CAN_NUM_OF_DRVBUF] = {
	/*- CAN message buffer management number = 0 */
	0x0000000,
	/*- CAN message buffer management number = 1 */
	0x2240000,
	/*- CAN message buffer management number = 2 */
	0x0000000
};
/* Start user code for global definition. Do not edit comment generated here */
/* End user code for global definition. Do not edit comment generated here */


/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function initializes CAN0.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void CAN0_Init(void)
{
	C0WUPMK = 1;	/* INTC0WUP disable */
	C0WUPIF = 0;	/* INTC0WUP IF clear */
	C0ERRMK = 1;	/* INTC0ERR disable */
	C0ERRIF = 0;	/* INTC0ERR IF clear */
	C0RECMK = 1;	/* INTC0REC disable */
	C0RECIF = 0;	/* INTC0REC IF clear */
	C0TRXMK = 1;	/* INTC0TRX disable */
	C0TRXIF = 0;	/* INTC0TRX IF clear */

	/* Set INTC0WUP lowest priority */
	C0WUPIC |= 0x07;
	C0WUPMK = 0;	/* INTC0WUP enable */

	/* Set INTC0ERR lowest priority */
	C0ERRIC |= 0x07;
	C0ERRMK = 0;	/* INTC0ERR enable */

	/* Set INTC0REC lowest priority */
	C0RECIC |= 0x07;
	C0RECMK = 0;	/* INTC0REC enable */

	/* Set INTC0TRX lowest priority */
	C0TRXIC |= 0x07;
	C0TRXMK = 0;	/* INTC0TRX enable */
	ISEL25 = 0;	/* select fXP1 as CAN0 clock */

	/* CAN0 CRXD0_P34 pin set */
	PFC3L &= 0xEF;
	PFCE3L |= 0x10;
	PMC3L |= 0x10;

	/* CAN0 CTXD0_P33 pin set */
	PFC3L &= 0xF7;
	PFCE3L |= 0x08;
	PMC3L |= 0x08;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function sets CAN0's clock and starts the CAN controller.
**
**	Parameters:
**		None
**
**	Returns:
**		MD_ARGERROR
**		MD_ALRDYSTA
**		MD_OK
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CAN0_Enable(void)
{
	MD_STATUS status = MD_OK;

	CanChEnable( 0 );
	status = CanChInit( 0 );

	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function sets CAN0 to normal operation mode.
**
**	Parameters:
**		None
**
**	Returns:
**		MD_ARGERROR
**		MD_ERROR
**		MD_OK
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CAN0_SetNormalMode(void)
{
	MD_STATUS status = MD_OK;

	status = CanChSetNrmMode( 0 );

	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function acquires the CAN-ID data and data length from CAN0's message buffer.
**
**	Parameters:
**		bufno:	buffer number
**		p_canid:	start address of area for storing CAN-ID
**		p_data:	start address of area for storing message data
**		p_dlc:	start address of area for storing message length
**
**	Returns:
**		MD_OK
**		MD_ARGERROR
**		MD_ERROR
**		MD_NOMSG
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CAN0_MsgGetIdDataDlc(UCHAR bufno, ULONG* p_canid, UCHAR* p_data, SCHAR* p_dlc)
{
	MD_STATUS status = MD_OK;

	status = CanMsgGetIdDatDlc( 0, bufno, p_canid, p_data, p_dlc );
	
	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function acquires the data and data length from CAN0's message buffer.
**
**	Parameters:
**		bufno:	buffer number
**		p_data:	start address of area for storing message data
**		p_dlc:	start address of area for storing message length
**
**	Returns:
**		MD_OK
**		MD_ARGERROR
**		MD_ERROR
**		MD_NOMSG
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CAN0_MsgGetDataDlc(UCHAR bufno, UCHAR* p_data, SCHAR* p_dlc)
{
	MD_STATUS status = MD_OK;

	status = CanMsgGetDatDlc(0, bufno, p_data, p_dlc);
	
	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function sets data to CAN0's message buffer.
**
**	Parameters:
**		bufno:	buffer number
**		p_data:	start address of area for storing message data
**
**	Returns:
**		MD_OK
**		MD_ARGERROR
**		MD_ERROR
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CAN0_MsgSetData(UCHAR bufno, UCHAR* p_data)
{
	MD_STATUS status = MD_OK;

	status = CanMsgSetDat(0, bufno, p_data);
	
	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function sets the CAN-ID data and data length to CAN0's message buffer.
**
**	Parameters:
**		bufno:	buffer number
**		canid:	CAN ID
**		p_data:	start address of area for storing message data
**		dlc:	data length
**
**	Returns:
**		MD_OK
**		MD_ARGERROR
**		MD_ERROR
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CAN0_MsgSetIdDataDlc(UCHAR bufno, ULONG canid, UCHAR* p_data, SCHAR dlc)
{
	MD_STATUS status = MD_OK;
	
	status = CanMsgSetIdDatDlc(0, bufno, canid, p_data, dlc);
	
	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function sets the transmit request bit in CAN0's message buffer.
**
**	Parameters:
**		bufno:	buffer number
**
**	Returns:
**		MD_ARGERROR
**		MD_ERROR
**		MD_OK
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CAN0_MsgTxReq(UCHAR bufno)
{
	MD_STATUS status = MD_OK;
	
	status = CanMsgTxReq(0, bufno);
	
	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function acquires the transmit request bit in CAN0's message buffer.
**
**	Parameters:
**		bufno:	buffer number
**
**	Returns:
**		MD_TRUE
**		MD_FALSE
**		MD_ARGERROR
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CAN0_MsgGetTxInfo(UCHAR bufno)
{
	MD_STATUS status = MD_OK;
	
	status = CanMsgGetTxInfo(0, bufno);

	return (status);
}

/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */


