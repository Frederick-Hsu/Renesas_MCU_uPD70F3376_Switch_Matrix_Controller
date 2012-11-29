/*****************************************************************************************
 * Program name	: Parse_UART2_Message.h
 *
 * Description	: Declaration and Prototype file.
 *		  The 2 files (header file and source file) is used to parse the message, 
 *		  which UART2 (i.e. the serial port COM2 communicating with PC) received, 
 *		  then catalog into various kinds of command/instruction types.
 *
 * Author	: XU ZAN
 * Date		: Mon.	Aug. 13, 2012
 * Copyright(C)		2010 --- 2012	Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 *****************************************************************************************/
 

#ifndef _PARSE_UART2_MESSAGE_H
#define _PARSE_UART2_MESSAGE_H

	/*===================================================================*/
	//  Includes :
	#include <string.h>
	#include "..\macrodriver.h"
	#include "..\utility.h"
	#include "..\Switch_Relay_Control\Switch_Relay_Control.h"
	
	/*===================================================================*/
	//  Macros :
	
	
	
	
	/*===================================================================*/
	//  Global variables :
	
	
	
	

	/*===================================================================*/
	//  Function prototypes :
	int Parse_UART2_Received_Message(char *sMesg);

	/***********************************************************************************/

	int handling_Switch_Relay_Control_cmd(char* sSwitch_Relay_Ctrl_cmd_Mesg);
	int handling_ADC_cmd(char* sADC_cmd_Mesg);
	int handling_DAC_cmd(char* sDAC_cmd_Mesg);
	int handling_DIN_cmd(char* sDIN_cmd_Mesg);
	int handling_DOUT_cmd(char* sDOUT_cmd_Mesg);
	int handling_CAN_cmd(char* sCAN_cmd_Mesg);
	int handling_LIN_cmd(char* sLIN_cmd_Mesg);
	int handling_PWM_cmd(char* sPWM_cmd_Mesg);

	/***********************************************************************************/

	int handling_Multi_Switches(char* sMulti_Switch_Ctrl_Cmd__Mesg);
	int handling_SwitchAction_1Command_unit(char* s1Command_unit);
	int handling_Batch_Switches(char* sBatch_Switch_Ctrl_Cmd_Mesg);
	int handling_SwitchAction_1Attribute_unit(char* s1Attribute_unit, PSTSwitch_CHn_State pCHn_State);
	
	
#endif	/*    _PARSE_UART2_MESSAGE_H    */

