/****************************************************************************************
 * File name	: handling_CAN_cmd.c
 * Description	: To parse / handle the CAN command in the handling_CAN_cmd.c (.h) 
 * 		  file-pair. Declare the handling functions for CAN command group.
 * Creator	: XU ZAN	[HSE-OT]
 * Creation date: Sun.	July 07, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 ****************************************************************************************/

#include "Parse_UART2_Message.h"
#include "handling_CAN_cmd.h"
#include "../macrodriver.h"
#include "../utility.h"
#include "../can.h"
#include "../CAN/CAN_Control.h"

#include <string.h>

extern int g_iErrorCodeNo;

int handling_CANWrite_cmd(char *sARGIN_CanWriteMesg)
{
	int iError = 0;
	
	unsigned int uiLen = strlen(sARGIN_CanWriteMesg),
				 uiPosOfCmdSeparator_Colon = strcspn(sARGIN_CanWriteMesg, ":"),
				 uiPosOfCmdSeparator_Space = 0;
	char sCanId[32] = {0};
	unsigned long ulCanId = 0x0000000000000000L;
	char sCanData[32] = {0x00};
	UCHAR bytCanData[8] = {0x00};
	char sCanIdData[64] = {0};
	
	if (uiPosOfCmdSeparator_Colon == uiLen)
	{
		g_iErrorCodeNo = -45;
		return g_iErrorCodeNo;
	}
	strncpy(sCanIdData, sARGIN_CanWriteMesg+uiPosOfCmdSeparator_Colon+1, 
			uiLen-uiPosOfCmdSeparator_Colon-2);
			
	uiPosOfCmdSeparator_Space = strcspn(sCanIdData, " ");
	strncpy(sCanId, sCanIdData, uiPosOfCmdSeparator_Space);
	strncpy(sCanData, sCanIdData+uiPosOfCmdSeparator_Space+1, 
			strlen(sCanIdData)-uiPosOfCmdSeparator_Space-1);
	
	iError = Convert_Str_To_Int(sCanId, &ulCanId);
	if (strlen(sCanData) % 2 != 0)
	{
		g_iErrorCodeNo = -46;
		iError = g_iErrorCodeNo;
		return iError;
	}
	iError = Parse_CAN_Data(sCanData, bytCanData);
	iError = CAN0_MsgSetIdDataDlc(1, ulCanId, bytCanData, (strlen(sCanData)/2 - 1));
    CAN0_MsgTxReq(1);
	return iError;
}

int Parse_CAN_Data(char sRawCanData[], unsigned char *sParsedCanData)
{
	int iError = 0;
	int iLen = strlen(sRawCanData);
	int iDataLen = 0;
	char sCanDataByte[2] = {0x00};
	int increment = 0, index = 0;
	
	if (strncmp(sRawCanData, "0X", 2) != 0)
	{
		iError = -47;
		return iError;
	}
	if (iLen % 2 != 0)
	{
		iError = -48;
		return iError;
	}
	iDataLen = iLen/2 - 1;
	for (index = 2; index <= iLen; index += 2)
	{
		strncpy(sCanDataByte, sRawCanData+index, 2);
		*(sParsedCanData + (increment++)) = (Convert_Hex_Char_To_Int(sCanDataByte[0]) << 4) + Convert_Hex_Char_To_Int(sCanDataByte[1]);
	}
	return iError;
}

int handling_CANRead_cmd(char *sARGIN_CanReadMesg)
{
	int iError = 0;
	
	return iError;
}

int handling_CANConfig_cmd(char *sARGIN_CanConfigMesg)
{
    int iError = 0;
    unsigned int uiPosOfCmdSeparator_Colon = strcspn(sARGIN_CanConfigMesg, ":"),
                 uiLen = strlen(sARGIN_CanConfigMesg),
                 uiPosOfCmdSeparator_Space = 0;
    char sCanConfigMesg[32] = {0x00}, sCanBaudRate[16] = {0x00};
    
    if (uiLen == uiPosOfCmdSeparator_Colon)
    {
        g_iErrorCodeNo = -49;
        return g_iErrorCodeNo;
    }
    strncpy(sCanConfigMesg, sARGIN_CanConfigMesg+uiPosOfCmdSeparator_Colon+1, uiLen-uiPosOfCmdSeparator_Colon-2);
    if (strncmp(sCanConfigMesg, "BAUD", 4) != 0)
    {
        g_iErrorCodeNo = -50;
        return g_iErrorCodeNo;
    }
    uiPosOfCmdSeparator_Space = strcspn(sCanConfigMesg, " ");
    strncpy(sCanBaudRate, sCanConfigMesg+uiPosOfCmdSeparator_Space+1, strlen(sCanConfigMesg)-uiPosOfCmdSeparator_Space-1);
    iError = Set_CAN_BaudRate(sCanBaudRate);
    return iError;
}

/*
 * END OF FILE  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 */

