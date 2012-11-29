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
**  Filename :	can_drv.c
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
/* Start user code for global definition. Do not edit comment generated here */
/* End user code for global definition. Do not edit comment generated here */


/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function initializes CAN channel.
**
**	Parameters:
**		chno:	channel number
**
**	Returns:
**		MD_OK
**		MD_ARGERROR
**		MD_ERROR
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CanChInit(SCHAR chno)
{
	UCHAR	drvchno;
	MD_STATUS status = MD_OK;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	/* Use Channel No */
	else if ((gcCanChIniUse[chno] & MSK_CH_USE) == 0) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		drvchno = (gcCanChIniUse[chno] & MSK_CH_DRVCHNO);	/* Set drvchno */
		{
			volatile CAN_ChRegType*	pChRegType;

			/* Set CAN module register address */
			pChRegType = (volatile CAN_ChRegType*)(gcCanRegBaseAddr[chno].pChRegBaseAddr);
			/* Check init mode */
			if ((pChRegType->CTRL & MSK_OPMODE) != CHK_INIT)
			{
				status = MD_ERROR;
			}
			else
			{
				/* Set baudrate */
				pChRegType->BRP = gcCanChIniBps[drvchno].CnBRP;
				pChRegType->BTR = gcCanChIniBps[drvchno].CnBTR;
				/* Set channel interrupt */
				pChRegType->IE = gcCanChIniInt[drvchno];
				/* Set mask resister */
				{
					ULONG	*pCh_mask;

					pCh_mask = (ULONG *)&gcCanChIniMask[drvchno][0];
					pChRegType->MASK1L =  (USHORT)(*(pCh_mask + 0) & MSK_MASKL);
					pChRegType->MASK1H = (USHORT)((*(pCh_mask + 0) & MSK_MASKH) >> 16);
					pChRegType->MASK2L =  (USHORT)(*(pCh_mask + 1) & MSK_MASKL);
					pChRegType->MASK2H = (USHORT)((*(pCh_mask + 1) & MSK_MASKH) >> 16);
					pChRegType->MASK3L =  (USHORT)(*(pCh_mask + 2) & MSK_MASKL);
					pChRegType->MASK3H = (USHORT)((*(pCh_mask + 2) & MSK_MASKH) >> 16);
					pChRegType->MASK4L =  (USHORT)(*(pCh_mask + 3) & MSK_MASKL);
					pChRegType->MASK4H = (USHORT)((*(pCh_mask + 3) & MSK_MASKH) >> 16);
				}

				{
					USHORT	ch_ini_macro;

					ch_ini_macro = (USHORT)(gcCanChIniMacro[drvchno]);	/* Get init data */
					/* Set error counter clear bit and the action of arbitration lost */
					pChRegType->CTRL = (((ch_ini_macro << 8) \
										| ((~ch_ini_macro) & (USHORT)MSK_REG_L)) \
										& (USHORT)(MSK_AL | MSK_CCERC));
				}

				{
					volatile CAN_GlbRegType*	pGlbRegType;

					/* Set CAN global register address */
					pGlbRegType = (volatile CAN_GlbRegType*)(gcCanRegBaseAddr[chno].pGlbRegBaseAddr);
					/* Set ABT delay */
					pGlbRegType->GMABTD = gcCanGlbIniMacro[chno];
				}

				{
					volatile CAN_MsgRegType*	pMsgRegType;

					/* Set CAN message buffer register address */
					pMsgRegType = (volatile CAN_MsgRegType *)(gcCanRegBaseAddr[chno].pMsgRegBaseAddr);
					/* CAN message buffer initialization */
					/* Init message buffer nouse */
					{
						UCHAR	num_of_buf;
						UCHAR	bufno;
						volatile CAN_MsgRegType*	pMsgRegTypeBuf;

						num_of_buf = gcCanChNumOfCanBuf[drvchno];
						/* Loop all message buffer */
						for( bufno = 0; bufno < num_of_buf; bufno++ ) 
						{
							/* Set CAN message buffer[n] register address */
							pMsgRegTypeBuf = &pMsgRegType[bufno];
							pMsgRegTypeBuf->MCTRL = CLR_RDY;	/* Clear RDY bit */
							pMsgRegTypeBuf->MCONF &= CLR_MAx;	/* Clear MA0 bit */
							pMsgRegTypeBuf->MCTRL = (USHORT)(CLR_TRQ | CLR_DN);	/* Clear TRQ, DN bit */
						}
					}

					/* Init message buffer initial value */
					{
						UCHAR	drvbufno_start;
						UCHAR	drvbufno_end;
						UCHAR	drvbufno;

						drvbufno_start = gcCanChDrvBufNoTop[drvchno];
						drvbufno_end = drvbufno_start + gcCanChDrvBufNoSize[drvchno];
						/* Loop use message buffer */
						for( drvbufno = drvbufno_start; drvbufno < drvbufno_end; drvbufno++ ) 
						{
							UCHAR	canbuf_ini_atr1;
							volatile CAN_MsgRegType2*	pMsgRegTypeBuf;

							canbuf_ini_atr1 = gcCanBufIniAtr1[drvbufno];
							/* Set CAN message buffer[n] register address */
							{
								UCHAR	bufno;

								bufno = gcCanBufIniBufno[drvbufno];
								pMsgRegTypeBuf = (volatile CAN_MsgRegType2*)&pMsgRegType[bufno];
							}

							pMsgRegTypeBuf->MCONF = canbuf_ini_atr1;	/* Set CnMCONFm resister */
							/* Set CnMIDHm, CnMIDLm resister */
							{
								ULONG		canbuf_ini_canid;

								canbuf_ini_canid = gcCanBufIniCanId[drvbufno];
								pMsgRegTypeBuf->MIDH = (USHORT)((canbuf_ini_canid & MSK_CANIDH) >> 16);
								pMsgRegTypeBuf->MIDL =  (USHORT)(canbuf_ini_canid & MSK_CANIDL);
							}

							/* Tx message buffer ? */
							if ((canbuf_ini_atr1 & MSK_MTx) == (UCHAR)CHK_MTx_TX) 
							{
								pMsgRegTypeBuf->MDLC = gcCanBufIniAtr2[drvbufno] & MSK_DLC;	/* Set CnMDLCm resister */
								/* Set CnMDATAm resister */
								(pMsgRegTypeBuf->MDATA)[0] = 0;
								(pMsgRegTypeBuf->MDATA)[1] = 0;
								(pMsgRegTypeBuf->MDATA)[2] = 0;
								(pMsgRegTypeBuf->MDATA)[3] = 0;
							}
							else
							{
								/* NOT RUN */
							}

							/* Set CnMCTRLm resister */
							{
								USHORT	IE;

								if ((gcCanBufIniAtr2[drvbufno] & MSK_IE) == 0) 
								{
									IE = CLR_IE;
								}
								else
								{
									IE = SET_IE;
								}
								pMsgRegTypeBuf->MCTRL = (USHORT)(CLR_MOW | IE | CLR_DN | CLR_TRQ);
							}
							pMsgRegTypeBuf->MCTRL = SET_RDY;	/* Set RDY bit */
						}
					}
				}
			}
		}
	}

	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function sets the CAN channel's clock and starts the CAN controller.
**
**	Parameters:
**		chno:	channel number
**
**	Returns:
**		MD_ARGERROR
**		MD_ALRDYSTA
**		MD_OK
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CanChEnable( SCHAR chno )
{
	MD_STATUS status = MD_OK;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	/* Check use Channel No */
	else if ((gcCanChIniUse[chno] & MSK_CH_USE) == 0) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		volatile CAN_GlbRegType*	pGlbRegType;

		/* Set CAN global register address */
		pGlbRegType = (volatile CAN_GlbRegType *)(gcCanRegBaseAddr[chno].pGlbRegBaseAddr);
		/* Check GOM bit */
		if ((pGlbRegType->GMCTRL & MSK_GOM) != 0) 
		{
			status = MD_ALRDYSTART;
		}
		/* Set CAN clock */
		else
		{
			/* Set drvchno */
			char	drvchno;
			drvchno = (gcCanChIniUse[chno] & MSK_CH_DRVCHNO);
			pGlbRegType->GMCS = gcCanChIniBps[drvchno].CnGMCS;
			pGlbRegType->GMCTRL = SET_GOM;	/* Start CAN controller */
		}
	}

	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function sets the CAN channel to init mode from operation mode.
**
**	Parameters:
**		chno:	channel number
**
**	Returns:
**		MD_ARGERROR
**		MD_ERROR
**		MD_OK
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CanChSetInitMode( SCHAR chno )
{
	MD_STATUS status = MD_OK;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	/* Check use channel No */
	else if ((gcCanChIniUse[chno] & MSK_CH_USE) == 0) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		volatile CAN_ChRegType*		pChRegType;

		/* Set CAN module register address */
		pChRegType = (volatile CAN_ChRegType *)(gcCanRegBaseAddr[chno].pChRegBaseAddr);
		/* Check not init mode */
		if ((pChRegType->CTRL & MSK_OPMODE) == CHK_INIT) 
		{
			status = MD_ERROR;
		}
		else
		{
			/* Set normal mode */
			pChRegType->CTRL = SET_INIT;
		}
	}

	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function sets the CAN channel to normal operation mode.
**
**	Parameters:
**		chno:	channel number
**
**	Returns:
**		MD_ARGERROR
**		MD_ERROR
**		MD_OK
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CanChSetNrmMode( SCHAR chno )
{
	MD_STATUS status = MD_OK;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	/* Check use channel No */
	else if ((gcCanChIniUse[chno] & MSK_CH_USE) == 0) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		volatile CAN_ChRegType*		pChRegType;

		/* Set CAN module register address */
		pChRegType = (volatile CAN_ChRegType*)(gcCanRegBaseAddr[chno].pChRegBaseAddr);
		/* Check init mode */
		if ((pChRegType->CTRL & MSK_OPMODE) != CHK_INIT) 
		{
			status = MD_ERROR;
		}
		else
		{
			pChRegType->CTRL = SET_NORM;	/* Set normal mode */
		}
	}

	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function acquires the CAN channel's operation mode and power-saving mode status.
**
**	Parameters:
**		chno:	channel number
**
**	Returns:
**		MD_ARGERROR
**		bit status when MSB = 0
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CanChGetMode( SCHAR chno )
{
	MD_STATUS status = MD_ARGERROR;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	/* Check use channel No */
	else if ((gcCanChIniUse[chno] & MSK_CH_USE) == 0) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		volatile CAN_ChRegType*		pChRegType;

		/* Set CAN module register address */
		pChRegType = (volatile CAN_ChRegType *)(gcCanRegBaseAddr[chno].pChRegBaseAddr);		
		/* Get operation mode and power save mode (Set return value) */
		status = ((MD_STATUS)(pChRegType->CTRL & (MSK_OPMODE | MSK_PSMODE)));
	}
	
	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function acquires the data and data length from the CAN channel's message buffer.
**
**	Parameters:
**		chno:	channel number
**		bufno:	buffer number
**		p_data:	start address of area for storing message data
**		p_dlc:	Start address of area for storing message length
**
**	Returns:
**		MD_OK
**		MD_ARGERROR
**		MD_ERROR
**		MD_NOMSG
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CanMsgGetDatDlc( SCHAR chno, UCHAR bufno, UCHAR* p_data, SCHAR* p_dlc )
{
	MD_STATUS status = MD_OK;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		UCHAR		ch_ini_use;

		ch_ini_use = gcCanChIniUse[chno];
		/* Check use channel No */
		if ((ch_ini_use & MSK_CH_USE) == 0) 
		{
			status = MD_ARGERROR;
		}
		/* Check CAN buffer No Max/Min */
		else if (gcCanChNumOfCanBuf[ch_ini_use & MSK_CH_DRVCHNO] <= bufno) 
		{
			status = MD_ARGERROR;
		}
		else
		{
			volatile CAN_MsgRegType*	pMsgRegType;
			volatile CAN_MsgRegType*	pMsgRegTypeBuf;

			/* Set CAN message buffer register address */
			pMsgRegType = (volatile CAN_MsgRegType*)(gcCanRegBaseAddr[chno].pMsgRegBaseAddr);
			/* Set CAN message buffer[n] register address */
			pMsgRegTypeBuf = &pMsgRegType[bufno];
			/* Check parameter (Use CAN Buffer No) */
			if ((pMsgRegTypeBuf->MCONF & MSK_MAx) == 0) 
			{
				status = MD_ARGERROR;
			}
			/* Check DN bit */
			else if ((pMsgRegTypeBuf->MCTRL & MSK_DN) == 0) 
			{
				status = MD_NOMSG;
			}			
			/* Clear DN bit */
			else
			{
				pMsgRegTypeBuf->MCTRL = CLR_DN;

				*p_dlc = (SCHAR)(pMsgRegTypeBuf->MDLC & MSK_DLC);	/* Get dlc */
				/* Get message data */
				{
					SCHAR	data_cnt;
					
					for( data_cnt = (SCHAR)0; ((data_cnt < *p_dlc) && (data_cnt < (SCHAR)LEN_CANDATA)); data_cnt++ ) 
					{
						*(p_data + (UINT)data_cnt) = (pMsgRegTypeBuf->MDATA[data_cnt]);
					}
				}
				/* Check DN and MUC bit */
				if ((pMsgRegTypeBuf->MCTRL & (MSK_DN | MSK_MUC)) != 0) 
				{
					status = MD_ERROR;
				}
				else
				{
					/* NOT RUN */
				}
			}
		}
	}

	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function acquires the the CAN-ID.
**
**	Parameters:
**		chno:	channel number
**		bufno:	buffer number
**		p_canid:	start address of area for storing CAN-ID
**		p_data:	start address of area for storing message data
**		p_dlc:	start address of area for storing message length
**
**	Returns:
**		MD_ARGERROR
**		MD_OK
**		MD_ERROR
**		MD_NOMSG
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CanMsgGetIdDatDlc(SCHAR chno, UCHAR bufno, ULONG* p_canid, UCHAR* p_data, SCHAR* p_dlc)
{
	MD_STATUS status = MD_OK;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		UCHAR	ch_ini_use;
		ch_ini_use = gcCanChIniUse[chno];

		/* Check use channel No */
		if ((ch_ini_use & MSK_CH_USE) == 0) 
		{
			status = MD_ARGERROR;
		}
		/* Check CAN buffer No Max/Min */
		else if (gcCanChNumOfCanBuf[ch_ini_use & MSK_CH_DRVCHNO] <= bufno) 
		{
			status = MD_ARGERROR;
		}
	    else
	    {
			volatile CAN_MsgRegType*	pMsgRegType;
			volatile CAN_MsgRegType*	pMsgRegTypeBuf;

			/* Set CAN message buffer register address */
			pMsgRegType = (volatile CAN_MsgRegType *)(gcCanRegBaseAddr[chno].pMsgRegBaseAddr);
			/* Set CAN message buffer[n] register address */
			pMsgRegTypeBuf = &pMsgRegType[bufno];
			/* Check parameter (Use CAN Buffer No)  */
			if ((pMsgRegTypeBuf->MCONF & MSK_MAx) == 0) 
			{
				status = MD_ARGERROR;
			}
			/* Check DN bit */
			else if ((pMsgRegTypeBuf->MCTRL & MSK_DN) == 0) 
			{
				status = MD_NOMSG;
			}
			else
			{
				ULONG midl, midh;
				
				/* Clear DN bit */
				pMsgRegTypeBuf->MCTRL = CLR_DN;
				/* Get CAN id */				
                midl = (ULONG)(pMsgRegTypeBuf->MIDL);
                midh = ((ULONG)(pMsgRegTypeBuf->MIDH));
				*p_canid = (midh << 16) | midl;				
				/* Get dlc */
				*p_dlc = (SCHAR)(pMsgRegTypeBuf->MDLC & MSK_DLC);
				/* Get message data */
				{
					SCHAR	data_cnt;
					
					for( data_cnt = (SCHAR)0; ((data_cnt < *p_dlc) && (data_cnt < (SCHAR)LEN_CANDATA)); data_cnt++ )
					{
						*(p_data + (UINT)data_cnt) = (pMsgRegTypeBuf->MDATA[data_cnt]);
					}
				}		
				/* Check DN and MUC bit */
				if ((pMsgRegTypeBuf->MCTRL & (MSK_DN | MSK_MUC)) != 0) 
				{
					status = MD_ERROR;
				}
				else
				{
					/* NOT RUN */
				}
			}
		}
	}

	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function sets data to the CAN channel's message buffer.
**
**	Parameters:
**		chno:	channel number
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
MD_STATUS CanMsgSetDat(SCHAR chno, UCHAR bufno, UCHAR* p_data)
{
	MD_STATUS status = MD_OK;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		UCHAR	ch_ini_use;

		ch_ini_use = gcCanChIniUse[chno];
		/* Check use channel No */
		if ((ch_ini_use & MSK_CH_USE) == 0) 
		{
			status = MD_ARGERROR;
		}
		/* Check CAN buffer No Max/Min */
		else if (gcCanChNumOfCanBuf[ch_ini_use & MSK_CH_DRVCHNO] <= bufno) 
		{
			status = MD_ARGERROR;
		}
		else
		{
			volatile CAN_MsgRegType*	pMsgRegType;
			volatile CAN_MsgRegType*	pMsgRegTypeBuf;

			/* Set CAN message buffer register address */
			pMsgRegType = (volatile CAN_MsgRegType*)(gcCanRegBaseAddr[chno].pMsgRegBaseAddr);
			/* Set CAN message buffer[n] register address */
			pMsgRegTypeBuf = &pMsgRegType[bufno];
			/* Check parameter (Use CAN Buffer No)  */
			if ((pMsgRegTypeBuf->MCONF & MSK_MAx) == 0) 
			{
				status = MD_ARGERROR;
			}
			/* Check TRQ bit */
			else if ((pMsgRegTypeBuf->MCTRL & MSK_TRQ) != 0) 
			{
				status = MD_ERROR;
			}
			else
			{
				/* Check RDY bit */
				pMsgRegTypeBuf->MCTRL = CLR_RDY;	/* Clear RDY bit */
				if ((pMsgRegTypeBuf->MCTRL & MSK_RDY) != 0) 
				{
					status = MD_ERROR;
				}
				else
				{
					SCHAR	dlc_msk;

					dlc_msk = (SCHAR)(pMsgRegTypeBuf->MDLC & MSK_DLC);	/* Get dlc */
					/* Set message data */
					{
						SCHAR	data_cnt;

						for( data_cnt = (SCHAR)0; ((data_cnt < (SCHAR)dlc_msk) && (data_cnt < (SCHAR)LEN_CANDATA)); data_cnt++ )
						{
							pMsgRegTypeBuf->MDATA[data_cnt] = *(p_data + (UINT)data_cnt);
						}
					}					
					pMsgRegTypeBuf->MCTRL = SET_RDY;	/* Set RDY bit */
				}
			}
		}
	}

	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function sets the CAN-ID, data and data length to the CAN channel's message buffer.
**
**	Parameters:
**		chno:	channel number
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
MD_STATUS CanMsgSetIdDatDlc(SCHAR chno, UCHAR bufno, ULONG canid, UCHAR* p_data, SCHAR dlc)
{
	MD_STATUS status = MD_OK;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		UCHAR	ch_ini_use;

		ch_ini_use = gcCanChIniUse[chno];
		/* Check use channel No */
		if ((ch_ini_use & MSK_CH_USE) == 0) 
		{
			status = MD_ARGERROR;
		}
		/* Check CAN buffer No Max/Min */
		else if (gcCanChNumOfCanBuf[ch_ini_use & MSK_CH_DRVCHNO] <= bufno) 
		{
			status = MD_ARGERROR;
		}
		else
		{
			volatile CAN_MsgRegType*	pMsgRegType;
			volatile CAN_MsgRegType*	pMsgRegTypeBuf;

			/* Set CAN message buffer register address */
			pMsgRegType = (volatile CAN_MsgRegType *)(gcCanRegBaseAddr[chno].pMsgRegBaseAddr);
			/* Set CAN message buffer[n] register address */
			pMsgRegTypeBuf = &pMsgRegType[bufno];
			/* Check parameter (Use CAN Buffer No)  */
			if ((pMsgRegTypeBuf->MCONF & MSK_MAx) == 0) 
			{
				status = MD_ARGERROR;
			}
			/* Check TRQ bit */
			else if ((pMsgRegTypeBuf->MCTRL & MSK_TRQ) != 0) 
			{
				status = MD_ERROR;
			}
			else
			{
				/* Check RDY bit */
				pMsgRegTypeBuf->MCTRL = CLR_RDY;	/* Clear RDY bit */
				if ((pMsgRegTypeBuf->MCTRL & MSK_RDY) != 0) 
				{
					status = MD_ERROR;
				}
				else
				{
					/* Set CAN id */
					pMsgRegTypeBuf->MIDH = (USHORT)((canid & MSK_CANIDH) >> 16);
					pMsgRegTypeBuf->MIDL = (USHORT)(canid & MSK_CANIDL);

					{
						SCHAR	dlc_msk;

						/* Set dlc */
						pMsgRegTypeBuf->MDLC = (UCHAR)(dlc_msk = (SCHAR)(dlc & MSK_DLC));
						/* Set message data */
						{
							SCHAR		data_cnt;

							for( data_cnt = (SCHAR)0; ((data_cnt < (SCHAR)dlc_msk) && (data_cnt < (SCHAR)LEN_CANDATA)); data_cnt++ )
							{
								pMsgRegTypeBuf->MDATA[data_cnt] = *(p_data + (UINT)data_cnt);
							}
						}
						/* Set RDY bit */
						pMsgRegTypeBuf->MCTRL = SET_RDY;
					}
				}
			}
		}
	}

	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function sets the transmit request bit in the CAN channel's message buffer.
**
**	Parameters:
**		chno:	channel number
**		bufno:	buffer number
**
**	Returns:
**		MD_ARGERROR
**		MD_ERROR
**		MD_OK
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CanMsgTxReq(SCHAR chno, UCHAR bufno)
{
	MD_STATUS status = MD_OK;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		UCHAR	ch_ini_use;

		ch_ini_use = gcCanChIniUse[chno];
		/* Check use channel No */
		if ((ch_ini_use & MSK_CH_USE) == 0) 
		{
			status = MD_ARGERROR;
		}
		else
		{
			/* CAN buffer No Max/Min */
			if (gcCanChNumOfCanBuf[ch_ini_use & MSK_CH_DRVCHNO] <= bufno) 
			{
				status = MD_ARGERROR;
			}
			else
			{
				volatile CAN_MsgRegType*	pMsgRegType;
				volatile CAN_MsgRegType*	pMsgRegTypeBuf;

				/* Set CAN message buffer register address */
				pMsgRegType = (volatile CAN_MsgRegType *)(gcCanRegBaseAddr[chno].pMsgRegBaseAddr);
				/* Set CAN message buffer[n] register address */
				pMsgRegTypeBuf = &pMsgRegType[bufno];
				/* Check parameter (Use CAN Buffer No)  */
				if ((pMsgRegTypeBuf->MCONF & MSK_MAx) == 0) 
				{
					status = MD_ARGERROR;
				}
				else
				{
					/* Check RDY bit */
					if ((pMsgRegTypeBuf->MCTRL & MSK_RDY) == 0) 
					{
						status = MD_ERROR;
					}
					else
					{
						pMsgRegTypeBuf->MCTRL = SET_TRQ;	/* Set TRQ bit */
					}
				}
			}
		}
	}

	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function acquires the transmit request bit in the CAN channel's message buffer.
**
**	Parameters:
**		chno:	channel number
**		bufno:	buffer number
**
**	Returns:
**		MD_ARGERROR
**		MD_TRUE
**		MD_FALSE
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CanMsgGetTxInfo(SCHAR chno, UCHAR bufno)
{
	MD_STATUS status = MD_TRUE;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		UCHAR		ch_ini_use;

		ch_ini_use = gcCanChIniUse[chno];
		/* Check use channel No */
		if ((ch_ini_use & MSK_CH_USE) == 0) 
		{
			status = MD_ARGERROR;
		}
		else
		{
			/* CAN buffer No Max/Min */
			if (gcCanChNumOfCanBuf[ch_ini_use & MSK_CH_DRVCHNO] <= bufno) 
			{
				status = MD_ARGERROR;
			}
			else
			{
				volatile CAN_MsgRegType*	pMsgRegType;
				volatile CAN_MsgRegType*	pMsgRegTypeBuf;

				/* Set CAN message buffer register address */
				pMsgRegType = (volatile CAN_MsgRegType*)(gcCanRegBaseAddr[chno].pMsgRegBaseAddr);
				/* Set CAN message buffer[n] register address */
				pMsgRegTypeBuf = &pMsgRegType[bufno];
				/* Check parameter (Use CAN Buffer No)  */
				if ((pMsgRegTypeBuf->MCONF & MSK_MAx) == 0) 
				{
					status = MD_ARGERROR;
				}
				else
				{
					/* Get TRQ bit */
					if ((pMsgRegTypeBuf->MCTRL & MSK_TRQ) == 0) 
					{
						status = MD_FALSE;
					}
					else
					{
						/* NOT RUN */
					}
				}
			}
		}
	}

	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function searches for the data update bit (DN bit) that has been set to the CAN channel.
**
**	Parameters:
**		chno:	channel number
**		bufno:	buffer number
**
**	Returns:
**		MD_ARGERROR
**		MD_NOMSG
**		buffer number found first when MSB = 0
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CanChSrchRxInfo(SCHAR chno, UCHAR bufno)
{
	UCHAR	ch_num_of_canbuf;
	MD_STATUS status = MD_NOMSG;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		UCHAR		ch_ini_use;

		ch_ini_use = gcCanChIniUse[chno];
		/* Check use channel No */
		if ((ch_ini_use & MSK_CH_USE) == 0) 
		{
			status = MD_ARGERROR;
		}
		else
		{
			/* Get the number of CAN Buffers */
			ch_num_of_canbuf = gcCanChNumOfCanBuf[ch_ini_use & MSK_CH_DRVCHNO];
			/* CAN buffer No Max/Min */
			if (ch_num_of_canbuf <= bufno) 
			{
				status = MD_ARGERROR;
			}
			else
			{
				volatile CAN_MsgRegType*	pMsgRegType;
				UCHAR	bufno_cnt;

				/* Set CAN message buffer register address */
				pMsgRegType = (volatile CAN_MsgRegType *)(gcCanRegBaseAddr[chno].pMsgRegBaseAddr);
				/* Check DN bit */
				for( bufno_cnt = bufno; bufno_cnt < ch_num_of_canbuf; bufno_cnt++ )
				{
					volatile CAN_MsgRegType*	pMsgRegTypeBuf;

					/* Set CAN message buffer[n] register address */
					pMsgRegTypeBuf = &pMsgRegType[bufno_cnt];
					/* Check DN bit */
					if ((pMsgRegTypeBuf->MCTRL & MSK_DN) != 0) 
					{
						status = ((MD_STATUS)(bufno_cnt));
					}
					else
					{
						/* NOT RUN */
					}
				}
			}
		}
	}

	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function acquires the CAN channel's status.
**
**	Parameters:
**		chno:	channel number
**
**	Returns:
**		MD_ARGERROR
**		bit status when MSB = 0
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CanChGetStatus(SCHAR chno)
{
	MD_STATUS status = MD_ARGERROR;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	/* Check use channel No */
	else if ((gcCanChIniUse[chno] & MSK_CH_USE) == 0) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		volatile CAN_ChRegType*	pChRegType;

		/* Set CAN module register address */
		pChRegType = (volatile CAN_ChRegType *)(gcCanRegBaseAddr[chno].pChRegBaseAddr);
		/* Get CAN status (Set return value) */
		status = ((MD_STATUS)(pChRegType->INTS & (MSK_CINTS2 | MSK_CINTS3 | MSK_CINTS4 | MSK_CINTS5)));
	}
	
	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function clears the CAN channel's status.
**
**	Parameters:
**		chno:	channel number
**		clrdat:	data specified by clear bit setting
**
**	Returns:
**		MD_ARGERROR
**		MD_OK
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CanChClrStatus( SCHAR chno, UCHAR clrdat )
{
	MD_STATUS status = MD_OK;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	/* Check use channel No */
	else if ((gcCanChIniUse[chno] & MSK_CH_USE) == 0) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		volatile CAN_ChRegType*	pChRegType;

		/* Set CAN module register address */
		pChRegType = (volatile CAN_ChRegType*)(gcCanRegBaseAddr[chno].pChRegBaseAddr);
		/* Clear CAN status */
		pChRegType->INTS = (USHORT)((clrdat) & (MSK_CINTS2 | MSK_CINTS3 | MSK_CINTS4 | MSK_CINTS5));
	}

	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function acquires the CAN channel's bus status.
**
**	Parameters:
**		chno:	channel number
**
**	Returns:
**		MD_ARGERROR
**		bit status when MSB = 0
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CanChGetBusStatus(SCHAR chno)
{
	MD_STATUS status = MD_ARGERROR;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	/* Check use channel No */
	else if ((gcCanChIniUse[chno] & MSK_CH_USE) == 0) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		volatile CAN_ChRegType*	pChRegType;

		/* Set CAN module register address */
		pChRegType = (volatile CAN_ChRegType *)(gcCanRegBaseAddr[chno].pChRegBaseAddr);
		status = ((MD_STATUS)(pChRegType->INFO & (MSK_BOFF | MSK_TECS | MSK_RECS)));
	}
	
	return (status);
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function forcibly shuts down CAN-controller.
**
**	Parameters:
**		chno:	channel number
**
**	Returns:
**		MD_ARGERROR
**		MD_ERROR
**		MD_OK
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CanChShutDown(SCHAR chno)
{
	MD_STATUS status = MD_OK;

	/* Check channel No Max/Min */
	if ((chno < 0) || (chno >= CAN_NUM_OF_CH)) 
	{
		status = MD_ARGERROR;
	}
	/* Check use channel No */
	else if ((gcCanChIniUse[chno] & MSK_CH_USE) == 0) 
	{
		status = MD_ARGERROR;
	}
	else
	{
		volatile CAN_GlbRegType*	pGlbRegType;

		/* Set CAN global register address */
		pGlbRegType = (volatile CAN_GlbRegType*)(gcCanRegBaseAddr[chno].pGlbRegBaseAddr);	
		pGlbRegType->GMCTRL = SET_EFSD;	/* Set EFSD bit */
		pGlbRegType->GMCTRL = CLR_GOM;	/* Clear GOM bit */		
		/* Check GOM bit */
		if ((pGlbRegType->GMCTRL & MSK_GOM) != 0) 
		{
			status = MD_ERROR;
		}
		else
		{
			/* NOT RUN */
		}
	}

	return (status);
}

/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */


