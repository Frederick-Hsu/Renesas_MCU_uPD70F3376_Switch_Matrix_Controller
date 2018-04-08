/********************************************************************************************
 * File name	: handling_command.c
 * Description	: Declare and implement to handle command for all action catelogues.
 * Creator	: XU ZAN [HSE-OT]
 * Creation date: Fri.	March 1, 2013
 * Copyright(C)	2010 --- 2013	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 ********************************************************************************************/

/****************************************************************************/
// Includeds :
#include <stdio.h>
#include <string.h>

#include "handling_command.h"
#include "handling_Switch_Relay_Control_cmd.h"
#include "handling_ADC_DAC_cmd.h"
#include "handling_DIO_cmd.h"
#include "handling_FIN_cmd.h"
#include "handling_PWM_cmd.h"
#include "handling_System_cmd.h"
#include "../utility.h"

#if !defined (FW_SIMULATION_TESTING_BASED_ON_VISUAL_STUDIO)
	#include "../serial.h"
	#include "../ADC_and_DAC/ADC_and_DAC.h"
#endif	/*  FW_SIMULATION_TESTING_BASED_ON_VISUAL_STUDIO  */

#if !defined (JUST_TESTING_PURPOSE)
	#include <math.h>
#endif	/*  #if defined (JUST_TESTINGPURPOSE)  */



/****************************************************************************/
// Global variables :
extern int g_iErrorCodeNo;



/****************************************************************************/
// Functions implementation :
int handling_Switch_Relay_Control_cmd(char* sSwitch_Relay_Ctrl_cmd_Mesg)
{
	int iError = 0;
	// char *pCmdStringHeadPtr = sSwitch_Relay_Ctrl_cmd_Mesg;

	const int iCmdSeparator_Semicolon = ';'	,
		  iCmdSeparator_Colon 	 = ':'	,
		  iCmdSeparator_Comma 	 = ','	,
		  iCmdSeparator_Space 	 = ' '	,
		  iCmdSeparator_Sigh	 = '!'	,
		  iCmdSeparator_Qmark	 = '?'	;

	unsigned int uiPosOfCmdSeparator_Semicolon 	= 0,	// ";"
		     uiPosOfCmdSeparator_Colon		= 0,	// ":"
		     uiPosOfCmdSeparator_Comma		= 0,	// ","
		     uiPosOfCmdSeparator_Space 		= 0,	// " "
		     uiPosOfCmdSeparator_Sigh		= 0,	// "!"
		     uiPosOfCmdSeparator_Qmark		= 0;	// "?"

	char sTemp_1CmdUnit_String[64] = {0},
	     sTempSubString[128] = {0};

	unsigned int uiLen = strlen(sSwitch_Relay_Ctrl_cmd_Mesg);
	/*
	 * Search and locate the position of these command separator.
	 * For command separator ";" and "," it can judge the command kind.
	 */
	uiPosOfCmdSeparator_Semicolon = strcspn(sSwitch_Relay_Ctrl_cmd_Mesg, ";");	// Note :
	uiPosOfCmdSeparator_Colon = strcspn(sSwitch_Relay_Ctrl_cmd_Mesg, ":");		// If the specified separator was not found, it will
	uiPosOfCmdSeparator_Comma = strcspn(sSwitch_Relay_Ctrl_cmd_Mesg, ",");		// return the length of string = strlen(sCmdMesg)
	uiPosOfCmdSeparator_Space = strcspn(sSwitch_Relay_Ctrl_cmd_Mesg, " ");		// Not the negative value.
	uiPosOfCmdSeparator_Sigh = strcspn(sSwitch_Relay_Ctrl_cmd_Mesg, "!");		// Remarked by XUZAN@2013-02-21
	uiPosOfCmdSeparator_Qmark = strcspn(sSwitch_Relay_Ctrl_cmd_Mesg, "?");

#if 1
	/*
	 * How to differentiate the command kind?
	 * please refer to the explanantion from file "How_to_implement_command_message_parsing.txt"
	 */

	/*START : Kind 2=========================================================*/
	// Corresponding to Kind 2: Multi parameters <----> Multi attributes
	if (uiPosOfCmdSeparator_Semicolon != uiLen)	// Search ";"
	{
		iError = handling_Multi_Switches(sSwitch_Relay_Ctrl_cmd_Mesg);
		if (iError)
		{
			g_iErrorCodeNo = iError;
			return g_iErrorCodeNo;
		}
	}
	/*END : Kind 2=========================================================*/

	/*START : Kind 3=========================================================*/
	// Corresponding to Kind 3: Single parameter <----> Multi attributes
	else if (uiPosOfCmdSeparator_Comma != uiLen)	// Search ","
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
	// Corresponding to Kind 1: Single parameter <----> Single attribute
	else
	{
		strncpy(sTemp_1CmdUnit_String, sSwitch_Relay_Ctrl_cmd_Mesg, uiLen-1);	// don't copy the last char '!'
		iError = handling_SwitchAction_1Command_unit(sTemp_1CmdUnit_String);
		if (iError)
		{
			g_iErrorCodeNo = iError;
			return g_iErrorCodeNo;
		}
	}
	/*END : Kind 1=========================================================*/
#endif
	return 0;
}

int handling_ADC_cmd(char* sADC_cmd_Mesg)
{
	int iResult = 0;

	unsigned int uiLen = strlen(sADC_cmd_Mesg),
		     uiPosOfCmdSeparator_Semicolon	= strcspn(sADC_cmd_Mesg, ";"),
		     uiPosOfCmdSeparator_Colon		= strcspn(sADC_cmd_Mesg, ":"),
		     uiPosOfCmdSeparator_Space		= strcspn(sADC_cmd_Mesg, " "),
		     uiPosOfCmdSeparator_Qmark		= strcspn(sADC_cmd_Mesg, "?");

	char sVoltageCurrent_MeasureType[16] = {0};
	char sADCMeasResultResponse[256] = {0};

	if (uiPosOfCmdSeparator_Qmark == uiLen)
	{
		g_iErrorCodeNo = -9;
		return g_iErrorCodeNo;
	}
	if (uiPosOfCmdSeparator_Colon == uiLen)
	{
		g_iErrorCodeNo = -10;
		return g_iErrorCodeNo;
	}

	strncpy(sVoltageCurrent_MeasureType, sADC_cmd_Mesg+uiPosOfCmdSeparator_Colon+1, 4);
	if (!strncmp(sVoltageCurrent_MeasureType, "VOLT", 4))
	{
		iResult = handling_Voltage_Measurement(sADC_cmd_Mesg, sADCMeasResultResponse);
		if (!iResult)
		{
			#if !defined (FW_SIMULATION_TESTING_BASED_ON_VISUAL_STUDIO)
			UARTD2_SendData(sADCMeasResultResponse, strlen(sADCMeasResultResponse));
			#endif	/*  FW_SIMULATION_TESTING_BASED_ON_VISUAL_STUDIO  */
		}
		g_iErrorCodeNo = iResult;
		return g_iErrorCodeNo;
	}
	else if (!strncmp(sVoltageCurrent_MeasureType, "CURR", 4))
	{
		iResult = handling_Current_Measurement(sADC_cmd_Mesg, sADCMeasResultResponse);
		if (!iResult)
		{
			#if !defined (FW_SIMULATION_TESTING_BASED_ON_VISUAL_STUDIO)
			UARTD2_SendData(sADCMeasResultResponse, strlen(sADCMeasResultResponse));
			#endif	/*  FW_SIMULATION_TESTING_BASED_ON_VISUAL_STUDIO  */
		}
		g_iErrorCodeNo = iResult;
		return g_iErrorCodeNo;
	}

/***************************************/
	return iResult;
}

int handling_DAC_cmd(char* sDAC_cmd_Mesg)
{
	int iResult = 0;

	unsigned int uiLen = strlen(sDAC_cmd_Mesg),
			     uiPosOfCmdSeparator_Colon = strcspn(sDAC_cmd_Mesg, ":"),
			     uiPosOfCmdSeparator_Space = strcspn(sDAC_cmd_Mesg, " ");

	char sDAC_OutputType[16] = {0}, sDAC_OutputVoltageValue[16] = {0};
	float fOutputVoltage = 0.0000f;

	strncpy(sDAC_OutputType,
		sDAC_cmd_Mesg+uiPosOfCmdSeparator_Colon+1,
		uiPosOfCmdSeparator_Space-uiPosOfCmdSeparator_Colon-1);

	ToUpperString(sDAC_OutputType);
	if (strncmp(sDAC_OutputType, "VOLT", 4))
	{
		g_iErrorCodeNo = -14;
		return g_iErrorCodeNo;
	}
	strncpy(sDAC_OutputVoltageValue, sDAC_cmd_Mesg+uiPosOfCmdSeparator_Space+1, uiLen-uiPosOfCmdSeparator_Space-2);

#if !defined (FW_SIMULATION_TESTING_BASED_ON_VISUAL_STUDIO)
	fOutputVoltage = atoff(sDAC_OutputVoltageValue);
#endif	/*  FW_SIMULATION_TESTING_BASED_ON_VISUAL_STUDIO  */
	/*
	 * Insert a judgement code here, you must judge the DAC outputing voltage value whether DAC can support.
	 * Otherwise, you could not get the voltage which you desired to output.

	if ((fOutputVoltage<=fMaxVoltage) && (fOutputVoltage>=fMinVoltage))
	{
		g_iErrorCodeNo = -15;
		return g_iErrorCodeNo;
	}
	 *
	 */
#if !defined (FW_SIMULATION_TESTING_BASED_ON_VISUAL_STUDIO)
	/*
	 * Do experiment to output 256 voltage values, test and verify the DAC voltage linearity.
	 * Just for debugging purpose.
	 *
	 * Remarked by Xu Zan@2013-05-28
	 */
	DAC_OutPut_Voltage_For_Debugging(atoi(sDAC_OutputVoltageValue));

	#if 0	// Temporarily disable this actual DAC_Outputing_Voltage block.	Modified by Xu Zan@2013-05-28
		#if defined (JUST_TESTING_PURPOSE)
			DAC_Output_Real_Voltage(fOutputVoltage);
		#else
			DAC_Output_Voltage(abs(floorf(fOutputVoltage)));
		#endif	/*  JUST_TESTING_PURPOSE  */
	#endif
#endif	/*  FW_SIMULATION_TESTING_BASED_ON_VISUAL_STUDIO  */

/***************************************/
	return iResult;
}

int handling_DIN_cmd(char* sDIN_cmd_Mesg)
{
	int iError = 0;

	unsigned int uiLen 							= strlen(sDIN_cmd_Mesg),
		     	 uiPosOfCmdSeparator_Semicolon 	= strcspn(sDIN_cmd_Mesg, ";"),
		     	 uiPosOfCmdSeparator_Qmark 		= strcspn(sDIN_cmd_Mesg, "?"),
		     	 uiPosOfStar 					= strcspn(sDIN_cmd_Mesg, "*");

	char sDIN_CHnStateResponse[256] = {0}, sDinCmdResponse[256] = {0};

	if (uiPosOfCmdSeparator_Qmark == uiLen)
	{
		g_iErrorCodeNo = -13;
		return g_iErrorCodeNo;
	}
	if (uiPosOfStar != uiLen)
	{
#if !defined (FW_SIMULATION_TESTING_BASED_ON_VISUAL_STUDIO)
		iError = handling_1GroupOfChs_DIN_cmd(sDIN_cmd_Mesg, sDIN_CHnStateResponse);
#endif
	}
	else if (uiPosOfCmdSeparator_Semicolon != uiLen)
	{
		iError = handling_MultiCH_DIN_cmd(sDIN_cmd_Mesg, sDIN_CHnStateResponse);
	}
	else
	{
		iError = handling_SingleCH_DIN_cmd(sDIN_cmd_Mesg, sDIN_CHnStateResponse);
	}
	if (iError)
	{
		g_iErrorCodeNo = iError;
		return iError;
	}
	sprintf(sDinCmdResponse, "$%s!", sDIN_CHnStateResponse);
	#if !defined (FW_SIMULATION_TESTING_BASED_ON_VISUAL_STUDIO)
		UARTD2_SendData(sDinCmdResponse, strlen(sDinCmdResponse));
	#endif	/*  FW_SIMULATION_TESTING_BASED_ON_VISUAL_STUDIO  */

/***************************/
	return iError;
}

int handling_FIN_cmd(char *sFIN_cmd_Mesg)
{
	int iError = 0;
	unsigned int uiLen 		  = strlen(sFIN_cmd_Mesg),
				 uiPosOfColon = strcspn(sFIN_cmd_Mesg, ":"),
				 uiPosOfQmark = strcspn(sFIN_cmd_Mesg, "?"),
				 uiPosOfStar  = strcspn(sFIN_cmd_Mesg, "*");
	char sFIN_CHnStateResponse[128] = {0}, sFINCmdResponse[128] = {0};
	
	if (uiPosOfQmark == uiLen)
	{
		g_iErrorCodeNo = -13;
		return g_iErrorCodeNo;
	}
	if (uiPosOfStar != uiLen)
		iError = handling_1GroupOfChs_FIN_cmd(sFIN_cmd_Mesg, sFIN_CHnStateResponse);
	else
		iError = handling_SingleCH_FIN_cmd(sFIN_cmd_Mesg, sFIN_CHnStateResponse);
	if (iError)
	{
		g_iErrorCodeNo = iError;
		return iError;
	}
	sprintf(sFINCmdResponse, "$%s!", sFIN_CHnStateResponse);
	
	#if !defined (FW_SIMULATION_TESTING_BASED_ON_VISUAL_STUDIO)
		UARTD2_SendData(sFINCmdResponse, strlen(sFINCmdResponse));
	#endif
	
/***************************/
	return iError;	
}

int handling_DOUT_cmd(char* sDOUT_cmd_Mesg)
{
	int iError = 0;

	unsigned int uiLen = strlen(sDOUT_cmd_Mesg),
                     uiPosOfCmdSeparator_Semicolon = strcspn(sDOUT_cmd_Mesg, ";"),
                     uiPosOfCmdSeparator_Colon = strcspn(sDOUT_cmd_Mesg, ":"),
                     uiPosOfCmdSeparator_Space = strcspn(sDOUT_cmd_Mesg, " ");

        if ((uiPosOfCmdSeparator_Colon == uiLen) ||
            (uiPosOfCmdSeparator_Space == uiLen) )
        {
                g_iErrorCodeNo = -19;
                return g_iErrorCodeNo;
        }

        if (uiPosOfCmdSeparator_Semicolon != uiLen)
        {
                iError = handling_Multi_DOUT_CHn_cmd(sDOUT_cmd_Mesg);
        }
        else
        {
                iError = handling_Single_DOUT_CHn_cmd(sDOUT_cmd_Mesg);
        }
/***************************/
	return iError;
}

int handling_PWM_cmd(char* sPWM_cmd_Mesg)
{
	int iError = 0;

	char sResponseMesg[256] = {0};
	ToUpperString(sPWM_cmd_Mesg);
	if (strncmp(sPWM_cmd_Mesg, "PWMO", 4) == 0)
	{
		iError = handling_PWMOut_cmd(sPWM_cmd_Mesg);
		#if !defined (FW_SIMULATION_TESTING_BASED_ON_VISUAL_STUDIO)
			sprintf(sResponseMesg, "$%s", sPWM_cmd_Mesg);
			UARTD2_SendData(sResponseMesg, strlen(sResponseMesg));
		#endif
	}
	else if (strncmp(sPWM_cmd_Mesg, "PWMI", 4) == 0)
	{
		iError = handling_PWMIn_cmd(sPWM_cmd_Mesg);
	}
	else
	{
		g_iErrorCodeNo = -23;
		return g_iErrorCodeNo;
	}

/***************************/
	return iError;
}

int handling_CAN_cmd(char* sCAN_cmd_Mesg)
{
	int iResult = 0;
	
	ToUpperString(sCAN_cmd_Mesg);
	if (strncmp(sCAN_cmd_Mesg, "CAN SET", 7) == 0)
	{
		iResult = handling_CANWrite_cmd(sCAN_cmd_Mesg);
	}
    /*
	else if (strncmp(sCAN_cmd_Mesg, "CAN GET", 7) == 0)
	{
		iResult = handling_CANRead_cmd(sCAN_cmd_Mesg);
	}
     */
    else if (strncmp(sCAN_cmd_Mesg, "CAN CONFIG", 10) == 0)
    {
        iResult = handling_CANConfig_cmd(sCAN_cmd_Mesg);
    }
	else
	{
		g_iErrorCodeNo = -44;
		return g_iErrorCodeNo;
	}

	return iResult;
}

int handling_LIN_cmd(char* sLIN_cmd_Mesg)
{
	int iResult = 0;

	return iResult;
}

int handling_System_cmd(char *sSystem_cmd_Mesg)
{
	int iError = 0;
	
	char sResponseMesg[256] = {0}, sSystemKeyword[32] = {0};
	int iPosOfColon = strcspn(sSystem_cmd_Mesg, ":");
	if (iPosOfColon == strlen(sSystem_cmd_Mesg))
	{
		g_iErrorCodeNo = -39;
		return g_iErrorCodeNo;
	}
	
	ToUpperString(sSystem_cmd_Mesg);
	strncpy(sSystemKeyword, sSystem_cmd_Mesg+iPosOfColon+1, 3);
	if (!strncmp(sSystemKeyword, "ERR", 3))
	{
		iError = handling_System_Error_cmd(sSystem_cmd_Mesg);
	}
	else if (!strncmp(sSystemKeyword, "IDN", 3))
	{
		iError = handling_System_IDN_cmd(sSystem_cmd_Mesg);
	}
	else if (!strncmp(sSystemKeyword, "VER", 3))
	{
		iError = handling_System_Version_cmd(sSystem_cmd_Mesg);
	}

/***************************/
	return iError;
}

/*
 * END OF FILE  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 */
