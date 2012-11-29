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
**  Filename :	can.h
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
#ifndef _MDCAN_
#define _MDCAN_
/*
*******************************************************************************
**	Register bit define
*******************************************************************************
*/
/* Total number of CAN channel */
#define	CAN_NUM_OF_CH				2

/* Infomation of programable I/O register */
#define	CAN_STP_PIO_CAN_BASE_ADDR	0x03FEC000

/*  CAN status clear macro */
#define	CAN_ERR_CLR_STS				(0x0004)	/* CAN error status */
#define	CAN_ERR_CLR_PRT				(0x0008)	/* CAN protocol error */
#define	CAN_ERR_CLR_ABL				(0x0010)	/* Arbitration lost */
#define	CAN_ERR_CLR_WAK				(0x0020)	/* Wakeup */

/*  CAN-ID format mode */
#define	CAN_CANID_EXT				(0x80000000)
#define	CAN_CANID_STD_MSK			(0x000007ff)
#define	CAN_CANID_EXT_MSK			(0x1fffffff)

/*  [Channel] gcCanChIniUse[] */
#define	CAN_INICH_USE				(0x80)

/*  [Channel] _cdc_u1g_ch_ini_int[] */
#define	CAN_INICH_INT_SET_TX		(0x0100)
#define	CAN_INICH_INT_SET_RX		(0x0200)
#define	CAN_INICH_INT_SET_ERRSTS	(0x0400)
#define	CAN_INICH_INT_SET_PRTERR	(0x0800)
#define	CAN_INICH_INT_SET_ARBLST	(0x1000)
#define	CAN_INICH_INT_SET_WAKUP		(0x2000)
#define	CAN_INICH_INT_CLR_TX		(0x0001)
#define	CAN_INICH_INT_CLR_RX		(0x0002)
#define	CAN_INICH_INT_CLR_ERRSTS	(0x0004)
#define	CAN_INICH_INT_CLR_PRTERR	(0x0008)
#define	CAN_INICH_INT_CLR_ARBLST	(0x0010)
#define	CAN_INICH_INT_CLR_WAKUP		(0x0020)

/*  [Message] gcCanBufIniAtr1[] */
#define	CAN_INIMSG_ADDRTYP_USE		(0x01)	/* CnCONFm.MA0-2 */
#define	CAN_INIMSG_MSGTYP_TX		(0x00)	/* CnCONFm.MT0-2 */
#define	CAN_INIMSG_MSGTYP_RX		(0x08)
#define	CAN_INIMSG_MSGTYP_MSK1		(0x10)
#define	CAN_INIMSG_MSGTYP_MSK2		(0x18)
#define	CAN_INIMSG_MSGTYP_MSK3		(0x20)
#define	CAN_INIMSG_MSGTYP_MSK4		(0x28)
#define	CAN_INIMSG_FRMTYP_DAT		(0x00)	/* CnCONFm.RTR */
#define	CAN_INIMSG_FRMTYP_RMT		(0x40)
#define	CAN_INIMSG_OVRWRT			(0x80)	/* CnCONFm.OWS */

/*  [Message] gcCanBufIniAtr2[] */
#define	CAN_INIMSG_IE				(0x80)	/* CnCTRLm.IE(*) */
											/* M_CTRLm.IE(*) */

/*
 *		Structure definition
 */
/*  Baud rate setup information */
typedef struct CAN_ChBpsInf {
	UCHAR	CnGMCS;	/* CnGMCS */
	UCHAR	CnBRP;	/* CnBRP */
	USHORT	CnBTR;	/* CnBTR */
} CAN_ChBpsInf;

/*  Programmable I/O register for CAN macro */
/* aFCAN global register */
typedef struct CAN_GlbRegType
{										/*															(offset) */
	volatile USHORT		GMCTRL;			/* CAN global macro control register						(+ 0x00) */
	volatile UCHAR		GMCS;			/* CAN global macro clock selection register				(+ 0x02) */
	volatile UCHAR		DummyGlb1;		/* <<< Dummy >>>											(+ 0x03) */
	volatile USHORT		DummyGlb2;		/* <<< Dummy >>>											(+ 0x04) */
	volatile USHORT		GMABT;			/* CAN global macro automatic block transmission register	(+ 0x06) */
	volatile UCHAR		GMABTD;			/* CAN global macro automatic block transmission delay register(+ 0x08) */
} CAN_GlbRegType;

/* aFCAN module register */
typedef struct CAN_ChRegType
{										/*														(offset) */
	volatile USHORT		MASK1L;			/* CAN module mask 1 register							(+ 0x00) */
	volatile USHORT		MASK1H;			/* CAN module mask 1 register							(+ 0x02) */
	volatile USHORT		MASK2L;			/* CAN module mask 2 register							(+ 0x04) */
	volatile USHORT		MASK2H;			/* CAN module mask 2 register							(+ 0x06) */
	volatile USHORT		MASK3L;			/* CAN module mask 3 register							(+ 0x08) */
	volatile USHORT		MASK3H;			/* CAN module mask 3 register							(+ 0x0a) */
	volatile USHORT		MASK4L;			/* CAN module mask 4 register							(+ 0x0c) */
	volatile USHORT		MASK4H;			/* CAN module mask 4 register							(+ 0x0e) */
	volatile USHORT		CTRL;			/* CAN module control register							(+ 0x10) */
	volatile UCHAR		LEC;			/* CAN module last error code register					(+ 0x12) */
	volatile UCHAR		INFO;			/* CAN module information register						(+ 0x13) */
	volatile USHORT		ERC;			/* CAN module error counter								(+ 0x14) */
	volatile USHORT		IE;				/* CAN module interrupt enable register					(+ 0x16) */
	volatile USHORT		INTS;			/* CAN module interupt status register					(+ 0x18) */
	volatile UCHAR		BRP;			/* CAN module bit-rate prescaler register				(+ 0x1a) */
	volatile UCHAR		DummyCh1;		/* <<< Dummy >>>										(+ 0x1b) */
	volatile USHORT		BTR;			/* CAN bit-rate register								(+ 0x1c) */
	volatile UCHAR		LIPT;			/* CAN module last in-pointer register					(+ 0x1e) */
	volatile UCHAR		DummyCh2;		/* <<< Dummy >>>										(+ 0x1b) */
	volatile USHORT		RGPT;			/* CAN module receive history list get pointer register	(+ 0x20) */
	volatile UCHAR		LOPT;			/* CAN module last out-pointer register					(+ 0x22) */
	volatile UCHAR		DummyCh3;		/* <<< Dummy >>>										(+ 0x23) */
	volatile USHORT		TGPT;			/* CAN module transmit history list get pointer register(+ 0x24) */
	volatile USHORT		TS;				/* CAN module time dtamp register						(+ 0x26) */
} CAN_ChRegType;

/* aFCAN message buffer register */
typedef struct CAN_MsgRegType
{										/*												(offset) */
	volatile UCHAR		MDATA[8];		/* Message data byte registers (8bit)			(+ 0x00) */
	volatile UCHAR		MDLC;			/* Message data length code register			(+ 0x08) */
	volatile UCHAR		MCONF;			/* Message configuration register				(+ 0x09) */
	volatile USHORT		MIDL;			/* Message identifier registers					(+ 0x0a) */
	volatile USHORT		MIDH;			/* Message identifier registers					(+ 0x0c) */
	volatile USHORT		MCTRL;			/* Message control register						(+ 0x0e) */
	volatile UCHAR		DummyMsg[16];	/* <<< Dummy : You can't delete this member.>>>	(+ 0x10) */
} CAN_MsgRegType;

/* aFCAN global register */
typedef struct CAN_RegBaseAddr
{
	CAN_GlbRegType*		pGlbRegBaseAddr;	/* CAN global register base address */
	CAN_ChRegType*		pChRegBaseAddr;		/* CAN module register base address */
	CAN_MsgRegType*		pMsgRegBaseAddr;	/* CAN message buffer register base address */
} CAN_RegBaseAddr;


/*
 *		Configuration file setup information
 */
/*  [Channel] gcCanChIniUse[] */
#define	MSK_CH_USE			(CAN_INICH_USE)
#define	MSK_CH_DRVCHNO		(0x0f)


/*  [Channel] gcCanChIniMask[] */
/*  [Channel] Number of mask register */
#define	CAN_NUM_OF_MASK	(4)
#define	MSK_MASKH			(0x1fff0000)
#define	MSK_MASKL			(0x0000ffff)


/*  [Message] gcCanBufIniAtr1[] */
#define	MSK_MTx				(0x38)
#define	CHK_MTx_TX			(0x00)


/*  [Message] gcCanBufIniAtr2[] */
#define	MSK_DLC				(0x0f)
#define	MSK_IE				(0x80)


/*  [Message] gcCanChIniMacro[] */
#define	MSK_TSEN			(0x0101)
#define	MSK_TSSEL			(0x0202)
#define	MSK_TSLOCK			(0x0404)
#define	MSK_AL				(0x4040)
#define	MSK_CCERC			(0x8000)
#define	MSK_REG_L			(0x00ff)


/*  [Message] gcCanBufIniCanId[] */
#define	MSK_CANIDH			(0xffff0000)
#define	MSK_CANIDL			(0x0000ffff)


/*  [Data] Configuration data external reference definition */
/* Device information */
extern const CAN_RegBaseAddr	gcCanRegBaseAddr[];

/* Global information */
extern const UCHAR				gcCanGlbIniMacro[];

/* Channel information */
extern const UCHAR				gcCanChIniUse[];
extern const USHORT				gcCanChIniInt[];
extern const CAN_ChBpsInf		gcCanChIniBps[];
extern const ULONG				gcCanChIniMask[][CAN_NUM_OF_MASK];
extern const UCHAR				gcCanChDrvBufNoTop[];
extern const UCHAR				gcCanChDrvBufNoSize[];
extern const UCHAR				gcCanChNumOfCanBuf[];

/* Message information */
extern const UCHAR				gcCanBufIniAtr1[];
extern const UCHAR				gcCanBufIniAtr2[];
extern const UCHAR				gcCanBufIniBufno[];
extern const ULONG				gcCanBufIniCanId[];
extern const UCHAR				gcCanChIniMacro[];


/*
 *		Parameter code
 */
/*  CAN data length */
#define	LEN_CANDATA			(8)


/*
 *		CAN register macro code (for aFCAN)
 */
/*  [Register] CnGMCTRL */
#define	MSK_GOM				(0x0001)
#define	CLR_GOM				(0x0001)
#define	SET_GOM				(0x0100)
#define	SET_EFSD			(0x0200)

/*  [Register] CnCTRL */
#define	MSK_OPMODE			(0x0007)
#define	MSK_PSMODE			(0x0018)
#define	CHK_INIT			(0x0000)
#define	CHK_NORM			(0x0001)
#define	CHK_ABT				(0x0002)
#define	CHK_RXONLY			(0x0003)
#define	CHK_SSHT			(0x0004)
#define	CHK_SELF			(0x0005)
#define	SET_INIT			(0x0007)
#define	SET_NORM			(0x0100)

/*  [Register] CnINTS */
#define	MSK_CINTS0			(0x0001)
#define	MSK_CINTS1			(0x0002)
#define	MSK_CINTS2			(0x0004)
#define	MSK_CINTS3			(0x0008)
#define	MSK_CINTS4			(0x0010)
#define	MSK_CINTS5			(0x0020)

/*  [Register] CnINFO */
#define	MSK_RECS			(0x03)
#define	MSK_TECS			(0x0c)
#define	MSK_BOFF			(0x10)

/*  [Register] CnMCTRLm */
#define	MSK_RDY				(0x0001)
#define	CLR_RDY				(0x0001)
#define	SET_RDY				(0x0100)
#define	MSK_TRQ				(0x0002)
#define	CLR_TRQ				(0x0002)
#define	SET_TRQ				(0x0200)
#define	MSK_DN				(0x0004)
#define	CLR_DN				(0x0004)
#define	SET_DN				(0x0400)
#define	CLR_IE				(0x0008)
#define	SET_IE				(0x0800)
#define	CLR_MOW				(0x0010)
#define	MSK_MUC				(0x2000)

/*  [Register] CnMCONFm */
#define	MSK_MAx				(0x07)
#define	CLR_MAx				(0xf8)

/*
 *		Structure definition
 */
/* aFCAN message buffer register type2 (for CnMDATAxxm) */
typedef struct CAN_MsgRegType2
{										/*													(offset) */
	volatile USHORT		MDATA[4];		/* Message data short registers	(16bit)				(+ 0x00) */
	volatile UCHAR		MDLC;			/* Message data length code register				(+ 0x08) */
	volatile UCHAR		MCONF;			/* Message configuration register					(+ 0x09) */
	volatile USHORT		MIDL;			/* Message identifier registers						(+ 0x0a) */
	volatile USHORT		MIDH;			/* Message identifier registers						(+ 0x0c) */
	volatile USHORT		MCTRL;			/* Message control register							(+ 0x0e) */
	volatile UCHAR		DummyMsg[16];	/* <<< Dummy : You can't delete this member. >>>	(+ 0x10) */
} CAN_MsgRegType2;

	/* Channel 0 */
#define	Ch0_Msg17		0x11	/* Tx message */
#define	Ch0_Msg08		0x08	/* Rx message */
#define	Ch0_Msg31		0x1F	/* Rx message */
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
/*
 *		Conversion macro
 */
#define	CAN_SET_STD_ID(id)				(id << 18)
#define	CAN_SET_EXT_ID(id)				(id | CAN_CANID_EXT)
#define	CAN_GET_STD_ID(id)				(id = (id >> 18) & 0x000007ff)
#define	CAN_GET_EXT_ID(id)				(id = id & CAN_CANID_EXT_MSK)

/*
 *		CAN device driver function
 */
MD_STATUS	CanChInit( SCHAR chno );
MD_STATUS	CanChEnable( SCHAR chno );
MD_STATUS	CanChSetInitMode( SCHAR chno );
MD_STATUS	CanChSetNrmMode( SCHAR chno );
MD_STATUS	CanChGetMode( SCHAR chno );
MD_STATUS	CanMsgSetDat( SCHAR chno, UCHAR bufno, UCHAR* p_data );
MD_STATUS	CanMsgSetIdDatDlc( SCHAR chno, UCHAR bufno, ULONG canid, UCHAR* p_data, SCHAR dlc );
MD_STATUS	CanMsgGetDatDlc( SCHAR chno, UCHAR bufno, UCHAR* p_data, SCHAR*  p_dlc );
MD_STATUS	CanMsgGetIdDatDlc( SCHAR chno, UCHAR bufno, ULONG* canid, UCHAR* p_data, SCHAR* dlc );
MD_STATUS	CanMsgTxReq( SCHAR chno, UCHAR bufno );
MD_STATUS	CanMsgGetTxInfo( SCHAR chno, UCHAR bufno );
MD_STATUS	CanChSrchRxInfo( SCHAR chno, UCHAR bufno );
MD_STATUS	CanChGetStatus( SCHAR chno );
MD_STATUS	CanChClrStatus( SCHAR chno, UCHAR clrdat );
MD_STATUS	CanChGetBusStatus( SCHAR chno );
MD_STATUS	CanChShutDown( SCHAR chno );

/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void CAN0_Init(void);
MD_STATUS CAN0_Enable(void);
MD_STATUS CAN0_SetNormalMode(void);
MD_STATUS CAN0_MsgGetDataDlc(UCHAR bufno, UCHAR* p_data, SCHAR* p_dlc);
MD_STATUS CAN0_MsgGetIdDataDlc(UCHAR bufno, ULONG* canid, UCHAR* p_data, SCHAR* dlc);
MD_STATUS CAN0_MsgSetData(UCHAR bufno, UCHAR* p_data);
MD_STATUS CAN0_MsgSetIdDataDlc(UCHAR bufno, ULONG canid, UCHAR* p_data, SCHAR dlc);
MD_STATUS CAN0_MsgTxReq(UCHAR bufno);
MD_STATUS CAN0_MsgGetTxInfo(UCHAR bufno);
__interrupt void MD_INTC0WUP(void);
__interrupt void MD_INTC0TRX(void);
__interrupt void MD_INTC0REC(void);
__interrupt void MD_INTC0ERR(void);
/* Start user code for definition. Do not edit comment generated here */
/* End user code for definition. Do not edit comment generated here */
#endif
