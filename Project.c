/************************************************************************************************************************************
 * Project name		: Switch_Matrix_Controller
 *
 * Program name		: Project.c
 * Description		: Describe this project, her property and purpose.
 *			: Some relative information about this project.
 *
 * Development team	: Software group, Operations Testing department, Hella (Shanghai) Electronics Co., Ltd.
 *			: 
 *			: Development project team :
 *			: 	Team leader : HENRY XING
 *			:	Hardware engineers : HENRY XING
 *			:	Software engineers : XU ZAN
 *
 * Author		: XU ZAN
 * Creation date	: Thu.	July 19, 2012
 *
 * Copyright(C)		2010 --- 2020
 * All rights reserved.
 * 
 ************************************************************************************************************************************/
 
#include <stdio.h>
#include "Project.h"
// #include "serial.h"
#include "version.h"


void PrintOut_Project_Information()
{
	UARTD2_SendData(THIS_PROJECT, strlen(THIS_PROJECT)*sizeof(char));
    UARTD2_WaitForSendDataCompleted();
	
    UARTD2_SendData(DEVICE, strlen(DEVICE)*sizeof(char));
    UARTD2_WaitForSendDataCompleted();
	
    UARTD2_SendData(PROPERTY_PURPOSE, strlen(PROPERTY_PURPOSE)*sizeof(char));
    UARTD2_WaitForSendDataCompleted();
	
    UARTD2_SendData(DEVELOPMENT_TEAM, strlen(DEVELOPMENT_TEAM)*sizeof(char));
    UARTD2_WaitForSendDataCompleted();
    
	UARTD2_SendData(COPYRIGHT, strlen(COPYRIGHT)*sizeof(char));
    UARTD2_WaitForSendDataCompleted();
	return;
}

void Display_SW_Version()
{
	UARTD2_SendData(CURRENT_VERSION, strlen(CURRENT_VERSION)*sizeof(char));
    UARTD2_WaitForSendDataCompleted();
	return;
}

