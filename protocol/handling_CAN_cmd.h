/****************************************************************************************
 * File name	: handling_CAN_cmd.h
 * Description	: To parse / handle the CAN command in the handling_CAN_cmd.c (.h) 
 * 		  file-pair. Declare the handling functions for CAN command group.
 * Creator	: XU ZAN	[HSE-OT]
 * Creation date: Sun.	July 07, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 ****************************************************************************************/

#ifndef HANDLING_CAN_CMD_H
#define HANDLING_CAN_CMD_H

	int handling_CANWrite_cmd(char *sARGIN_CanWriteMesg);
	int handling_CANRead_cmd(char *sARGIN_CanReadMesg);
    int handling_CANConfig_cmd(char *sARGIN_CanConfigMesg);
	
	int Parse_CAN_Data(char sRawCanData[], unsigned char *sParsedCanData);

#endif	/*  HANDLING_CAN_CMD_H  */

