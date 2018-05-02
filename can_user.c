/*
*******************************************************************************
**
**  This device driver was created by Applilet2 for V850ES/Fx3
**  32-Bit Single-Chip Microcontrollers
**
**  Copyright(C) 2002, 2012 Renesas Electronics Corporation
**  All rights reserved by Renesas Electronics Corporation.
**
**  This program should be used on your own responsibility.
**  Renesas Electronics Corporation assumes no responsibility for any losses
**  incurred by customers or third parties arising from the use of this file.
**
**  Filename :	can_user.c
**  Abstract :	This file implements device driver for CAN module.
**  APIlib :	Applilet2 for V850ES/Fx3 V2.43 [30 Mar 2011]
**
**  Device :	uPD70F3376
**
**  Compiler :	CA850
**
**  Creation date:	09/26/2012
**  
*******************************************************************************
*/

#pragma interrupt INTC0WUP MD_INTC0WUP
#pragma interrupt INTC0REC MD_INTC0REC
#pragma interrupt INTC0TRX MD_INTC0TRX
#pragma interrupt INTC0ERR MD_INTC0ERR
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include "macrodriver.h"
#include "can.h"
/* Start user code for include definition. Do not edit comment generated here */
/* End user code for include definition. Do not edit comment generated here */
#include "user_define.h"
#include "CAN/CAN_Control.h"
#include "CAN/can_telegrams_circular_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global definition. Do not edit comment generated here */
/* End user code for global definition. Do not edit comment generated here */


/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTC0WUP interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__interrupt void MD_INTC0WUP(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTC0TRX interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__interrupt void MD_INTC0TRX(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTC0REC interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/

static CanGetMode_t gMode = IMMEDIATE;

#if (TELEGRAM_ARRAY_TYPE == TELEGRAM_ARRAY_TYPE1)
    static TelegramsCircularQueue_t queue = {NULL, 0, 0, 0};
#elif (TELEGRAM_ARRAY_TYPE == TELEGRAM_ARRAY_TYPE2)
    static TelegramsCircularQueue_t queue = {{0x00}, 0, 0, 0};
#endif

__interrupt void MD_INTC0REC(void)
{
	/* Start user code. Do not edit comment generated here */
	USHORT canid = 0;
	UCHAR candata[8] = {0x00};
	SCHAR len = 0;
    UCHAR canTelegram[64] = {0x00};
    UCHAR canMesg[17] = {0x00};
    int index = 0;
    UCHAR mesg[3] = {0x00};
    
	CAN0_MsgGetIdDataDlc(6, &canid, candata, &len);
	canid = canid & 0x000007FF;
    
    for (index = 0; index < len; index++)
    {
        sprintf(mesg, "%02X", candata[index]);
        strcat(canMesg, mesg);
    }
    
    if (Retrieve_CAN_ReceiveMode() == IMMEDIATE)
    {
        sprintf(canTelegram, "$CAN GET:0x%04X 0x%s!", canid, canMesg);
        UARTD2_SendData(canTelegram, strlen(canTelegram));
    }
    else if (Retrieve_CAN_ReceiveMode() == CACHE)
    {
        sprintf(canTelegram, "$CAN GET:0x%04X 0x%s!", canid, canMesg);
        EnqueueIntoTelegramsCircularQueue(&queue, canTelegram);
    }
	/* End user code. Do not edit comment generated here */
}

int Set_CAN_ReceiveMode(char sModeInfo[])
{
    int iError = 0;
    if (0 ==strcmp(sModeInfo, "IMMEDIATE"))
    {
        gMode = IMMEDIATE;
        DestroyTelegramsCircularQueue(&queue);
    }
    else if (0 == strcmp(sModeInfo, "CACHE"))
    {
        gMode = CACHE;
        InitTelegramsCircularQueue(&queue);
    }
    else
    {
        iError = -52;
    }
    return iError;
}

void PrintOutCanTelegram(Telegram oneItem)
{
    UCHAR mesg[64] = {0x00};
    sprintf(mesg, "%s\n", oneItem);
    UARTD2_SendData(mesg, strlen(mesg));
}

int CAN0_GetAllTelegram(void)
{
    return ReverselyFetchTelegrams(queue, MAX_CIRCULAR_QUEUE_SIZE, PrintOutCanTelegram);
}

int CAN0_GetLatestTelegram(void)
{
    return ReverselyFetchTelegrams(queue, 1, PrintOutCanTelegram);
}

CanGetMode_t Retrieve_CAN_ReceiveMode(void)
{
    return gMode;
}


/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function is INTC0ERR interrupt service routine.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
__interrupt void MD_INTC0ERR(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */


