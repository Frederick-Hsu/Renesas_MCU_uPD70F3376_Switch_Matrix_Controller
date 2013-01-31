/********************************************************************************************
 * Program name	: handling_Switch_Relay_Control_cmd.c
 * Description	: This file is to parse the command of controlling switch and relays, 
 *				: and more to call the corresponding function to implement them.
 * Author		: XU ZAN
 * Date			: Sat.	Sept. 22, 2012
 * Copyright(C)		2010 --- 2012		Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 ********************************************************************************************/


/****************************************************************************/
// Includeds :
#include "Parse_UART2_Message.h"

/*************************************************************************/
//  External global variables :
#include "..\heap_memory_area.h"
extern int __sysheap[SIZEOF_HEAP>>2];
extern size_t __sizeof_sysheap;


/****************************************************************************/
// Variables :
extern int g_iErrorCodeNo;




int handling_Switch_Relay_Control_cmd(char* sSwitch_Relay_Ctrl_cmd_Mesg)
{
	int iError = 0;
	char *pCmdStringHeadPtr = sSwitch_Relay_Ctrl_cmd_Mesg;

	const static int iCmdSeperator_Semicolon = ';',
			 iCmdSeperator_Colon = ':',
			 iCmdSeperator_Comma = ',',
			 iCmdSeperator_Blank = ' ';


	unsigned int uiPosOfCmdSeperator_Colon = 0,		// ":"
		     uiPosOfCmdSeperator_Blank = 0,		// " "
		     uiPosOfCmdSeperator_Comma = 0,		// ","
		     uiPosOfCmdSeperator_Semicolon = 0;		// ";"

	char *pIndexOfSeperator_Semicolon = NULL,	// ";"
	     *pIndexOfSeperator_Colon = NULL,		// ":"
	     *pIndexOfSeperator_Blank = NULL,		// " "
	     *pIndexOfSeperator_Comma = NULL,		// ","
	     *pIndexOfTerminalSignChar = NULL;		// "!"

	char sTemp_1CmdUnit_String[128] = {0},	// for example : <Action_Catalog> <Parameter1>:<Attribute1>;   "SWITch 0x5F:05 OFF;"
	     sTempSubString[256] = {0},
	     sRestSubStringOfCmdMesg[256] = {0};

	// uiPosOfCmdSeperator_Semicolon = strcspn(sSwitch_Relay_Ctrl_cmd_Mesg, ";");

	/*START : Kind 2=========================================================*/
	// Corresponding to Kind 2:
	pIndexOfSeperator_Semicolon = strchr(sSwitch_Relay_Ctrl_cmd_Mesg, iCmdSeperator_Semicolon);	// Search ";"
	if (pIndexOfSeperator_Semicolon != NULL)
	{
		iError = handling_Multi_Switches(sSwitch_Relay_Ctrl_cmd_Mesg);
		if (iError)
		{
			g_iErrorCodeNo = iError;
			return g_iErrorCodeNo;
		}
	}
	/*END : Kind 2=========================================================*/
	else
	{
		/*START : Kind 3=========================================================*/
		// Corresponding to Kind 3:
		pIndexOfSeperator_Colon = strchr(sSwitch_Relay_Ctrl_cmd_Mesg, iCmdSeperator_Comma);	// Search ","
		if (pIndexOfSeperator_Colon != NULL)
		{
			iError = handling_Batch_Switches(sSwitch_Relay_Ctrl_cmd_Mesg);
			if (iError)
			{
				g_iErrorCodeNo = iError;
				return g_iErrorCodeNo;
			}
		}
		/*END : Kind 3=========================================================*/

		/*START : Kind 1=========================================================*/
		// Corresponding to Kind 1:
		else
		{
			strncpy(sTemp_1CmdUnit_String, pCmdStringHeadPtr, strlen(pCmdStringHeadPtr)-1);
			iError = handling_SwitchAction_1Command_unit(sTemp_1CmdUnit_String);
			if (iError)
			{
				g_iErrorCodeNo = iError;
				return g_iErrorCodeNo;
			}
		}
		/*END : Kind 1=========================================================*/
	}

	return 0;
}

int handling_Multi_Switches(char* sMulti_Switch_Ctrl_Cmd_Mesg)
{ 
	int iResult = 0;

	unsigned int uiPosOfSemicolon = 0,
		     uiPosOfColon = 0,
		     uiPosOfBlank = 0;
		     
	char sTemp_1CmdUnit_String[128] = {0},
	     sRestSubStringOfCmdMesg[256] = {0},
	     sTempRestSubString[256] = {0};

	uiPosOfSemicolon = strcspn(sMulti_Switch_Ctrl_Cmd_Mesg, ";");	// Search the 1st semicolon (;)
	uiPosOfColon = strcspn(sMulti_Switch_Ctrl_Cmd_Mesg, ":");		// Search the 1st colon (:)
	uiPosOfBlank = strcspn(sMulti_Switch_Ctrl_Cmd_Mesg, " ");
	if ( (uiPosOfSemicolon < uiPosOfColon) || (uiPosOfColon < uiPosOfBlank) )
	{
		g_iErrorCodeNo = -1;
		return g_iErrorCodeNo;
	}

	/*
	 * Get the sub-string : "<Action_catalog> <Parameter1>:<Attribute1>;"
	 */
	strncpy(sTemp_1CmdUnit_String, sMulti_Switch_Ctrl_Cmd_Mesg, uiPosOfSemicolon);
	/*
	 * Get the rest sub-string of current complete command message
	 */
	strncpy(sRestSubStringOfCmdMesg, 
		sMulti_Switch_Ctrl_Cmd_Mesg+uiPosOfSemicolon+1, 
		strlen(sMulti_Switch_Ctrl_Cmd_Mesg)-uiPosOfSemicolon);

	iResult = handling_SwitchAction_1Command_unit(sTemp_1CmdUnit_String);
	if (iResult)
	{
		g_iErrorCodeNo = iResult;
		return g_iErrorCodeNo;
	}

	do
	{
		/*
		 * Before sTemp_1CmdUnit_String was assigned new string, 
		 * you must clean up the old string
		 */
		memset(sTemp_1CmdUnit_String, 0, strlen(sTemp_1CmdUnit_String)*sizeof(char));
		uiPosOfSemicolon = strcspn(sRestSubStringOfCmdMesg, ";");
		if (uiPosOfSemicolon == 0)
		{
			break;
		}
		strncpy(sTemp_1CmdUnit_String, sRestSubStringOfCmdMesg, uiPosOfSemicolon);

		iResult = handling_SwitchAction_1Command_unit(sTemp_1CmdUnit_String);
		if (iResult)
		{
			g_iErrorCodeNo = iResult;
			return g_iErrorCodeNo;
		}

		/*
		 * Get the rest sub-string from previous rest sub-string, 
		 * besides the 1 complete command unit string which was intercepted above.
		 */
		memset(sTempRestSubString, 0, strlen(sTempRestSubString)*sizeof(char));
		strncpy(sTempRestSubString, 
			sRestSubStringOfCmdMesg+uiPosOfSemicolon+1, 
			strlen(sRestSubStringOfCmdMesg)-uiPosOfSemicolon); 
		
		memset(sRestSubStringOfCmdMesg, 0, strlen(sRestSubStringOfCmdMesg)*sizeof(char));
		memcpy(sRestSubStringOfCmdMesg, sTempRestSubString, strlen(sTempRestSubString)*sizeof(char));
	}
	while (strchr(sRestSubStringOfCmdMesg, ';') != NULL);

	memset(sTemp_1CmdUnit_String, 0, strlen(sTemp_1CmdUnit_String)*sizeof(char));
	strncpy(sTemp_1CmdUnit_String, sRestSubStringOfCmdMesg, strlen(sRestSubStringOfCmdMesg)-1);
	iResult = handling_SwitchAction_1Command_unit(sTemp_1CmdUnit_String);
	if (iResult)
	{
		g_iErrorCodeNo = iResult;
		return g_iErrorCodeNo;
	}

	return iResult;
}
int handling_SwitchAction_1Command_unit(char* s1Command_unit)
/*************************************************************
 * "Switch action 1 command unit" format is :
 * <Action_catalog> <Parameter>:<Attribute>;
 * for example : SWITCH 0x5F:12 OFF;
 * 0x5F ---> Switch matrix board ID
 * 12   ---> Individual switch channel
 * OFF  ---> Switch state
 *************************************************************/
{
	int iResult = 0;

	unsigned int uiPosOfColon = 0, uiPosOfBlank = 0;

	char sActionCatalogString[256] = {0}, 
		 sSwitchMatrixBoardID[16] = {0}, 
		 sSwitchCH[16] = {0}, 
		 sSwitchState[16] = {0};

	PST_Access_Ctrl_SwitchRelayMatrix pSwitch = (PST_Access_Ctrl_SwitchRelayMatrix)malloc(sizeof(ST_Access_Ctrl_SwitchRelayMatrix));

	long lValue = 0;

	char sTempSubString[128] = {0};
	unsigned int uiLen_1Command_unit = strlen(s1Command_unit);

	uiPosOfColon = strcspn(s1Command_unit, ":");
	uiPosOfBlank = strcspn(s1Command_unit, " ");	// Search the 1st blank " " character and its position.

	strncpy(sActionCatalogString, s1Command_unit, uiPosOfBlank);
	ToUpperString(sActionCatalogString);
	if (strncmp(sActionCatalogString, "SWIT", 4) != 0)
	{
		g_iErrorCodeNo = -7;
		return g_iErrorCodeNo;
	}

	if (uiPosOfColon > uiPosOfBlank)
	{
		/*************************************************************************************************************************/
		// Get the switch matrix board ID from Patameter string
		strncpy(sSwitchMatrixBoardID, (s1Command_unit+uiPosOfBlank+1), (uiPosOfColon-uiPosOfBlank-1));
		// strncpy(sSwitchMatrixBoardID, s1Command_unit, (uiPosOfColon-uiPosOfBlank-1));
		iResult = Convert_Str_To_Int(sSwitchMatrixBoardID, &lValue);

		if (!iResult)
		{
			if ( (lValue > 0xFF) || (lValue < 0x00) )
			{
				g_iErrorCodeNo = -3;
				return g_iErrorCodeNo;
			}
			else
			{
				pSwitch->byteBoardID = (BYTE)lValue;
			}
		}
		else
		{
			g_iErrorCodeNo = -3;
			return g_iErrorCodeNo;
		}


		/*************************************************************************************************************************/
		// Get the switch channel and state from the Attribute string
		strncpy(sTempSubString, s1Command_unit+uiPosOfColon+1, uiLen_1Command_unit-uiPosOfColon);
		uiPosOfBlank = strcspn(sTempSubString, " ");
		strncpy(sSwitchCH, sTempSubString, uiPosOfBlank);
		strncpy(sSwitchState, (sTempSubString+uiPosOfBlank+1), (strlen(sTempSubString)-uiPosOfBlank));

		iResult = Convert_Str_To_Int(sSwitchCH, &lValue);
		if (!iResult)
		{
			if ( (lValue > 24) || (lValue < 0) )
			{
				g_iErrorCodeNo = -5;
				return g_iErrorCodeNo;
			}
			else
			{
				pSwitch->dwSwitch_Relay_CHn = (DWORD)lValue;
			}
		}
		else
		{
			g_iErrorCodeNo = -5;
			return g_iErrorCodeNo;
		}

		ToUpperString(sSwitchState);
		if ( (strncmp(sSwitchState, "ON", 2) == 0) || (strncmp(sSwitchState, "1", 1) == 0) || (strncmp(sSwitchState, "CLOSE", 5) == 0) )
		{
			pSwitch->eOpen_Close_State = ON;
		}
		else if ( (strncmp(sSwitchState, "OFF", 3) == 0) || (strncmp(sSwitchState, "0", 1) == 0) || (strncmp(sSwitchState, "OPEN", 4) == 0) )
		{
			pSwitch->eOpen_Close_State = OFF;
		}
		else
		{
			g_iErrorCodeNo = -6;
			return g_iErrorCodeNo;
		}
	}
	else
	{
		g_iErrorCodeNo = -4;
		return g_iErrorCodeNo;
	}

	// Control_Single_Switch(pSwitch);
	free(pSwitch);

	return iResult;
}


int handling_Batch_Switches(char* sBatch_Switch_Ctrl_Cmd_Mesg)
{
	int iResult = 0;

	char sActionCatalog[16] = {0}, 
		 sSwitchMatrixBoardID[16] = {0},
		 sAttributeListString[512] = {0},
		 s1Attribute_unit[32] = {0},
		 sRestSubStringOfAttributeList[512] = {0},
		 sTempRestSubString[512] = {0};
	
	unsigned int uiPosOfBlank = 0,	// Position of " "
				 uiPosOfColon = 0,	//             ":"
				 uiPosOfComma = 0;	//             ","

	PSTSwitch_CHn_State pSwitch_CH_State = (PSTSwitch_CHn_State)malloc(sizeof(STSwitch_CHn_State));
	BYTE bytSwitchBoardID = 0;
	long lTempValue = 0;
	/*===================================================================================================================*/


	uiPosOfBlank = strcspn(sBatch_Switch_Ctrl_Cmd_Mesg, " ");	// Search the seperators : the 1st blank ( ) and 
	uiPosOfColon = strcspn(sBatch_Switch_Ctrl_Cmd_Mesg, ":");	// the 1st colon (:)  Get their positions.
	if (uiPosOfColon <= uiPosOfBlank)
	{
		g_iErrorCodeNo = -1;
		return g_iErrorCodeNo;
	}

	strncpy(sActionCatalog, sBatch_Switch_Ctrl_Cmd_Mesg, uiPosOfBlank);
	ToUpperString(sActionCatalog);
	if (strncmp(sActionCatalog, "SWIT", 4) != 0)	// Check whether the action catalog keyword 'SWITCH' is right
	{
		g_iErrorCodeNo = -7;
		return g_iErrorCodeNo;
	}

	strncpy(sSwitchMatrixBoardID, sBatch_Switch_Ctrl_Cmd_Mesg+uiPosOfBlank+1, uiPosOfColon-uiPosOfBlank-1);	// Get BoardID
	iResult = Convert_Str_To_Int(sSwitchMatrixBoardID, &lTempValue);
	if (iResult)
	{
		g_iErrorCodeNo = -3;
		return g_iErrorCodeNo;
	}
	if ( (lTempValue > 0xFF) || (lTempValue < 0x00))
	{
		g_iErrorCodeNo = -3;
		return g_iErrorCodeNo;
	}
	bytSwitchBoardID = (BYTE)lTempValue;
	/*===================================================================================================================*/


	strncpy(sAttributeListString, 
			sBatch_Switch_Ctrl_Cmd_Mesg+uiPosOfColon+1, 
			strlen(sBatch_Switch_Ctrl_Cmd_Mesg)-uiPosOfColon);
	uiPosOfComma = strcspn(sAttributeListString, ",");
	uiPosOfBlank = strcspn(sAttributeListString, " ");
	if (uiPosOfComma < uiPosOfBlank)
	{
		g_iErrorCodeNo = -1;
		return g_iErrorCodeNo;
	}
	strncpy(s1Attribute_unit, sAttributeListString, uiPosOfComma);
	strncpy(sRestSubStringOfAttributeList, sAttributeListString+uiPosOfComma+1, strlen(sAttributeListString)-uiPosOfComma);
	
	iResult = handling_SwitchAction_1Attribute_unit(s1Attribute_unit, pSwitch_CH_State);
	if (iResult)
	{
		g_iErrorCodeNo = iResult;
		return g_iErrorCodeNo;
	}
	// Control_Batch_Switch(bytSwitchBoardID, pSwitch_CH_State);

	do 
	{
		memset(s1Attribute_unit, 0, strlen(s1Attribute_unit)*sizeof(char));
		uiPosOfComma = strcspn(sRestSubStringOfAttributeList, ",");
		if (uiPosOfComma == 0)
		{
			break;
		}
		strncpy(s1Attribute_unit, sRestSubStringOfAttributeList, uiPosOfComma);

		iResult = handling_SwitchAction_1Attribute_unit(s1Attribute_unit, pSwitch_CH_State);
		if (iResult)
		{
			g_iErrorCodeNo = iResult;
			return g_iErrorCodeNo;
		}
		// Control_Batch_Switch(bytSwitchBoardID, pSwitch_CH_State);

		/*************************************************************************************************/
		memset(sTempRestSubString, 0, strlen(sTempRestSubString)*sizeof(char));
		strncpy(sTempRestSubString, 
				sRestSubStringOfAttributeList+uiPosOfComma+1, 
				strlen(sRestSubStringOfAttributeList)-uiPosOfComma);
		memset(sRestSubStringOfAttributeList, 0, strlen(sRestSubStringOfAttributeList)*sizeof(char));
		memcpy(sRestSubStringOfAttributeList, sTempRestSubString, strlen(sTempRestSubString)*sizeof(char));
	}
	while (strchr(sRestSubStringOfAttributeList, ',') != NULL);

	memset(s1Attribute_unit, 0, strlen(s1Attribute_unit)*sizeof(char));
	strncpy(s1Attribute_unit, sRestSubStringOfAttributeList, strlen(sRestSubStringOfAttributeList)-1); 
	iResult = handling_SwitchAction_1Attribute_unit(s1Attribute_unit, pSwitch_CH_State);
	if (iResult)
	{
		g_iErrorCodeNo = iResult;
		return g_iErrorCodeNo;
	}
	// Control_Batch_Switch(bytSwitchBoardID, pSwitch_CH_State);

	free(pSwitch_CH_State);
	return iResult;
}


int handling_SwitchAction_1Attribute_unit(char* s1Attribute_unit, PSTSwitch_CHn_State pCHn_State)
{
	int iResult = 0;

	unsigned int uiPosOfBlank = 0;
	char sSwitchChannel[16] = {0}, sSwitchState[16] = {0};

	long lTempValue = 0;

	uiPosOfBlank = strcspn(s1Attribute_unit, " ");
	if (uiPosOfBlank == 0)
	{
		g_iErrorCodeNo = -1;
		return g_iErrorCodeNo;
	}
	strncpy(sSwitchChannel, s1Attribute_unit, uiPosOfBlank);
	strncpy(sSwitchState, s1Attribute_unit+uiPosOfBlank+1, strlen(s1Attribute_unit)-uiPosOfBlank);

	iResult = Convert_Str_To_Int(sSwitchChannel, &lTempValue);
	if (iResult)
	{
		g_iErrorCodeNo = -5;
		return g_iErrorCodeNo;
	}
	if ( (lTempValue>24) || (lTempValue<0) )
	{
		g_iErrorCodeNo = -5;
		return g_iErrorCodeNo;
	}
	pCHn_State->dwSwitcch_Relay_CHn = (DWORD)lTempValue;

	ToUpperString(sSwitchState);
	if ( (strncmp(sSwitchState, "ON", 2)==0) || (strncmp(sSwitchState, "CLOSE", 5)==0) || (strncmp(sSwitchState, "1", 1)==0) )
	{
		pCHn_State->eOpen_Close_State = ON;
	}
	else if ( (strncmp(sSwitchState, "OFF", 3)==0) || (strncmp(sSwitchState, "OPEN", 4)==0) || (strncmp(sSwitchState, "0", 1)==0) )
	{
		pCHn_State->eOpen_Close_State = OFF;
	}
	else
	{
		g_iErrorCodeNo = -6;
		return g_iErrorCodeNo;
	}


	return iResult;
}

