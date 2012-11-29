/**************************************************************************************************
 * Program name	: Switch_Relay_Control.c
 * Description	: This file declares that how to control the switches and relais on the switch
 *		: matrix board and relay matrix board.
 *		: 
 *		: Switches : ON / OFF,  CLOSE / OPEN
 *		: Relais   : CONNECTED / DISCONNECTED
 * Author	: XU ZAN
 * Date		: Fri.	July 27, 2012
 * Copyright(C)		2010 --- 2012		Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 **************************************************************************************************/


#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "Switch_Relay_Control.h"
#include "..\bus.h"

void Control_Single_Switch(PST_Access_Ctrl_SwitchRelayMatrix pSingleSwitchCHn)
{
	DWORD iCHn = pSingleSwitchCHn->dwSwitch_Relay_CHn;
	E_SWITCH_STATE eLEVEL = pSingleSwitchCHn->eOpen_Close_State;
	// Step 1 :
	
	/*
	 * Shielding the influence on ADC and DAC circuit.
	 */
	ENAD = LOW;
	ENDA = HIGH;
	
	CS0 = LOW;	
	// Step 2 :
	Write_Address_Bus(pSingleSwitchCHn->byteBoardID);
	
	// Step 3 :
	Write_DataBus_Single_CHn(iCHn-1, eLEVEL);	
	
	/* A short delay should be inserted here.
	 *
	 * At last, must remember to disable chip 74ALS520.
	 * Because it could influence other card.
	 */
	CS0 = HIGH;
}

void Control_Multi_Switch(PST_Access_Ctrl_SwitchRelayMatrix pSwitchCHi, ...)	
{
	va_list ap;
	PST_Access_Ctrl_SwitchRelayMatrix next = pSwitchCHi;
	
	va_start(ap, pSwitchCHi);
	
	while (next != NULL)
	{
		Control_Single_Switch(next);	// This statement must be executed firstly here
		next = va_arg(ap, PST_Access_Ctrl_SwitchRelayMatrix);
	}
	va_end(ap);
	
	return;
}


void Control_Batch_Switch(BYTE byteBoardID,
			  PSTSwitch_CHn_State pCHn_State, ...)
{
	va_list marker;
	PSTSwitch_CHn_State next = pCHn_State;
	
	/*
	 * Shielding the influence on ADC and DAC circuit.
	 */
	ENAD = LOW;
	ENDA = HIGH;
	
	CS0 = LOW;
	
	Write_Address_Bus(byteBoardID);
	
	va_start(marker, pCHn_State);
	while (next != NULL)
	{
		Write_DataBus_Single_CHn((next->dwSwitcch_Relay_CHn)-1, 
					 (next->eOpen_Close_State));
		next = va_arg(marker, PSTSwitch_CHn_State);
	}
	va_end(marker);
	
	CS0 = HIGH;
	return;
}



void Uniformly_Control_One_Switch_Board(BYTE iBoardID, E_SWITCH_STATE eUniformState)
{
	DWORD iCHn = 0;

	/*
	 * Shielding the influence on ADC and DAC circuit.
	 */
	ENAD = LOW;
	ENDA = HIGH;
	
	CS0 = LOW;	
	Write_Address_Bus(iBoardID);
	
	for (iCHn=1; iCHn<=24; iCHn++)
	{
		Write_DataBus_Single_CHn(iCHn-1, eUniformState);
	}
	
	CS0 = HIGH;
	return;	
}

