/**************************************************************************************************
 * Program name	: Switch_Relay_Control.h
 * Description	: This file declares that how to control the switches and relais on the switch
 *		: matrix board and relay matrix board.
 *		: 
 *		: Switches : ON / OFF,  CLOSE / OPEN
 *		: Relais   : CONNECTED / DISCONNECTED
 * Author	: XU ZAN
 * Date		: Thu.	July 26, 2012
 * Copyright(C)		2010 --- 2012		Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 **************************************************************************************************/


#ifndef _SWITCH_RELAY_CONTROL_H
#define _SWITCH_RELAY_CONTROL_H

	#include "..\macrodriver.h"

	
	typedef enum SWITCH_STATE
	{					
		OFF = 0,		
		OPEN = 0,		
		DISCONNECTED = 0,	
		
		ON = 1,			
		CLOSE = 1,		
		CONNECTED = 1
	}
	E_SWITCH_STATE;
	
	
	/*
	 * To access a switch or relay and control her state, it depends on 3 arguments :
	 * 	1. Switch Matrix Board ID,
	 * 	2. Switch number (or channel),
	 * 	3. State --- ON/OFF (or OPEN/CLOSE)
	 * 
	 */
	typedef struct Access_Control_SwitchRelayMatrix
	{
		/*
		 * The Switch-Relay-Matrix-Card Board ID was expressed in 8-bit byte.
		 */
		BYTE byteBoardID;
		/*
		 * The switch/relay number(or channel) was expressed in 32-bit DWORD,
		 * but there are maximal 24 switch channels in 1 matrix-card.
		 * 
		 * Attention please, the switch number starts from 1st channel, ends with 24th channel,
		 * not from CH0 to CH23
		 */
		DWORD dwSwitch_Relay_CHn;
		/*
		 * Specify the state of switch or relay.
		 */
		E_SWITCH_STATE eOpen_Close_State;
	}
	ST_Access_Ctrl_SwitchRelayMatrix, *PST_Access_Ctrl_SwitchRelayMatrix;
	
	
	typedef struct Switch_CHn_State
	{
		DWORD dwSwitcch_Relay_CHn;
		E_SWITCH_STATE eOpen_Close_State;
	}
	STSwitch_CHn_State, *PSTSwitch_CHn_State;
	
	
	
	
	
/*=========================================================================================================*/
	
	void Control_Single_Switch(PST_Access_Ctrl_SwitchRelayMatrix pSingleSwitchCHn);
	
	void Control_Multi_Switch(PST_Access_Ctrl_SwitchRelayMatrix pSwitchCHi, ...);
	
	void Control_Batch_Switch(BYTE 			byteBoardID,
				  PSTSwitch_CHn_State 	pCHn_State, ...);
	
	void Uniformly_Control_One_Switch_Board(BYTE iBoardID, E_SWITCH_STATE eUniformState);


#endif	/*    _SWITCH_RELAY_CONTROL_H    */

