/******************************************************************************************
 * Program name	: Digital_IN.C
 * Description	: The implementation for Digital_IN module.
 * Author	: XU ZAN
 * Date		: Thu.	July 26, 2012
 * Copyright(C)		2010 --- 2012	Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 ******************************************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include "Digital_IN.h"
#include "..\bus.h"
#include "..\serial.h"


	void Read_DIN_CHn_State(P_DIN_CHm_STATE pDInCHmState)
	{
		unsigned int uiDIN_CHn = 24;
		enum LEVEL eDIN_CHm_LEVEL;
		
		unsigned char sErrMesg[] = "The Digital IN channel is wrong.\n CH state is unknown.\n";
		
		DWORD dwDigitalInBusValue = 0x00000000;
		dwDigitalInBusValue = Read_Digital_In_Bus_Value();
		
		uiDIN_CHn = pDInCHmState->eCHm;
		if (uiDIN_CHn >= 24)
		{
			pDInCHmState->eCHm_State = 3;
			UARTD2_SendData(sErrMesg, sizeof(sErrMesg));
			return;
		}
		
		if ( ((dwDigitalInBusValue & (0x00000001 << uiDIN_CHn)) >> uiDIN_CHn) == HIGH )
		{
			eDIN_CHm_LEVEL = HIGH;
		}
		else if ( ((dwDigitalInBusValue & (0x00000001 << uiDIN_CHn)) >> uiDIN_CHn) == LOW )
		{
			eDIN_CHm_LEVEL = LOW;
		}
		else
		{
			eDIN_CHm_LEVEL = 3;	// Unknown state
		}
		
		pDInCHmState->eCHm_State = eDIN_CHm_LEVEL;
		return;
	}
	
	
	void Read_DIN_Multi_CHs_State(P_DIN_CHm_STATE pCHiState, ...)
	{
		va_list marker;
		
		P_DIN_CHm_STATE next = pCHiState;
		
		va_start(marker, pCHiState);
		while (next != NULL)
		{
			Read_DIN_CHn_State(next);
			next = va_arg(marker, P_DIN_CHm_STATE);
		}
		va_end(marker);
		
		return;
	}

