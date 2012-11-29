/*****************************************************************************************
 * Program name	: Parse_UART2_Message.c
 *
 * Description	: Implementation file.
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

/***********************************************************************/
// Includes :
#include "Parse_UART2_Message.h"
#include "error_code.h"


/***********************************************************************/
// Global variables :
int g_iErrorCodeNo = 0;



/***********************************************************************/
// Function implementation
int Parse_UART2_Received_Message(char *sMesg)
{
	int iResult = -1;
	size_t i = 0;
	unsigned int uiPosOfCharInString = 0;
	
	unsigned int uiTempSpecificCharPosition = 0;
	
	char sCommand_Group[64] = "",
	     sAction_Catalog[64] = "";
	char sTempSubString[1024] = {0};
	char cTempChar = '0';
	     
	char cCommand_Type[2] = "";
	
	unsigned int uiLengthOfMesg = strlen(sMesg);
	
	/*
	 * Firstly, it is a must to check the prefix '$' and suffix '!' of the command message.
	 * Remarked by XU ZAN @2012-09-16
	 */
	if ( !( (strcspn(sMesg, "$") == 0) &&
	        (strcspn(sMesg, "!") == uiLengthOfMesg-1) ) )
	{
		/*
		 * Please take good care about the error handling.
		 * Each error shoule be assign a specific error code number.
		 * 
		 * Added by XU ZAN @2012-09-20
		 */
		g_iErrorCodeNo = -1;
		return -1;	// It stands for "Command Syntax error".
	}

	/* Check the command type : Request or Query(?) */
	strncpy(cCommand_Type, (sMesg + uiLengthOfMesg - 2), 1);
	
	{
		uiTempSpecificCharPosition = strcspn(sMesg, ":");	// To get the position of 1st specific character colon(:)

		strncpy(sCommand_Group, sMesg+1, uiTempSpecificCharPosition-1);
		ToUpperString(sCommand_Group);
	}

	if (strncmp(sCommand_Group, "ACTI", 4) == 0)
	{
		{
			strncpy(sTempSubString, sMesg+uiTempSpecificCharPosition+1, uiLengthOfMesg-1);
			uiTempSpecificCharPosition = strcspn(sTempSubString, " ");
			strncpy(sAction_Catalog, sTempSubString, uiTempSpecificCharPosition);
			ToUpperString(sAction_Catalog);
		}

		if (strncmp(sAction_Catalog, "SWIT", 4) == 0)	// Catalog : "Switch (or Relay) control" command
		{
			iResult = handling_Switch_Relay_Control_cmd(sTempSubString);
			g_iErrorCodeNo = iResult;
			return iResult;
		}
		else if (strncmp(sAction_Catalog, "ADC", 3) == 0)	// Catalog : "ADC measuring" command
		{
			iResult = handling_ADC_cmd(sTempSubString);
			g_iErrorCodeNo = iResult;
			return iResult;
		}
		else if (strncmp(sAction_Catalog, "DAC", 3) == 0)	// Catalog : "DAC driving" command
		{
			iResult = handling_DAC_cmd(sTempSubString);
			g_iErrorCodeNo = iResult;
			return iResult;
		}
		else if (strncmp(sAction_Catalog, "DIN", 3) == 0)	// Catalog : "Digital IN" command
		{
			iResult = handling_DIN_cmd(sTempSubString);
			g_iErrorCodeNo = iResult;
			return iResult;
		}
		else if (strncmp(sAction_Catalog, "DOUT", 4) == 0)	// Catalog : "Digital OUT" command
		{
			iResult = handling_DOUT_cmd(sTempSubString);
			g_iErrorCodeNo = iResult;
			return iResult;
		}
		else if (strncmp(sAction_Catalog, "CAN", 3) == 0)	// Catalog : "CAN bus telegram" command
		{
			iResult = handling_CAN_cmd(sTempSubString);
			g_iErrorCodeNo = iResult;
			return iResult;
		}
		else if (strncmp(sAction_Catalog, "LIN", 3) == 0)	// Catalog : "LIN bus telegram" command
		{
			iResult = handling_LIN_cmd(sTempSubString);
			g_iErrorCodeNo = iResult;
			return iResult;
		}
		else if (strncmp(sAction_Catalog, "PWM", 3) == 0)	// Catalog : "PWM output" command
		{
			iResult = handling_PWM_cmd(sTempSubString);
			g_iErrorCodeNo = iResult;
			return iResult;
		}
		else
		{
			g_iErrorCodeNo = -2;
			return -2;
		}
	}
	else if (strncmp(sCommand_Group, "SYST", 4) == 0)
	{
	}
	else
	{
	}
	
/***********************************/
	return 0;
}

