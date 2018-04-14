/****************************************************************************************
 * File name    : CAN_Control.c
 * Description  : Configure some CAN settings in this CAN module.
 * Creator      : Frederick Hsu
 * Creation date: Sun.  09 April, 2018
 * Copyright(C) 2018    All rights reserved.
 *
 ****************************************************************************************/

#include "../macrodriver.h"
#include "../can.h"
#include "CAN_Control.h"
#include <string.h>

#pragma ioreg

MD_STATUS ChangeCanChBaudRate(SCHAR chno, UCHAR CnBRP, USHORT CnBTR)
{
	UCHAR	drvchno;
	MD_STATUS status = MD_OK;
    
    UCHAR brp;
    USHORT btr;

	{
		drvchno = (gcCanChIniUse[chno] & MSK_CH_DRVCHNO);	/* Set drvchno */
		{
			volatile CAN_ChRegType*	pChRegType;

			/* Set CAN module register address */
			pChRegType = (volatile CAN_ChRegType*)(gcCanRegBaseAddr[chno].pChRegBaseAddr);
			/* Check init mode */
			if ((pChRegType->CTRL & MSK_OPMODE) != CHK_INIT)
			{
				status = MD_ERROR;
			}
			else
			{
				/* Set baudrate */
				// pChRegType->BRP = gcCanChIniBps[drvchno].CnBRP;
                pChRegType->BRP = CnBRP;
				// pChRegType->BTR = gcCanChIniBps[drvchno].CnBTR;
                pChRegType->BTR = CnBTR;
                
                brp = C0BRP;
                btr = C0BTR;
			}
		}
	}

	return (status);
}

int Set_CAN_BaudRate(char sBaudRateInfo[])
{
    int iError = 0;
    if ((0 == strcmp(sBaudRateInfo, "1000KBPS")) || (0 == strcmp(sBaudRateInfo, "1000K")))
    {
        iError = CanChSetInitMode(0);
        iError = ChangeCanChBaudRate(0, 0x01, 0x0706);
        CAN0_SetNormalMode();
    }
    else if ((0 == strcmp(sBaudRateInfo, "500KBPS")) || (0 == strcmp(sBaudRateInfo, "500K")))
    {
        iError = CanChSetInitMode(0);
        iError = ChangeCanChBaudRate(0, 0x03, 0x0706);
        CAN0_SetNormalMode();
    }
    else if ((0 == strcmp(sBaudRateInfo, "250KBPS")) || (0 == strcmp(sBaudRateInfo, "250K")))
    {
        iError = CanChSetInitMode(0);
        iError = ChangeCanChBaudRate(0, 0x0F, 0x0203);
        CAN0_SetNormalMode();
    }
    else if ((0 == strcmp(sBaudRateInfo, "125KBPS")) || (0 == strcmp(sBaudRateInfo, "125K")))
    {
        iError = CanChSetInitMode(0);
        iError = ChangeCanChBaudRate(0, 0x0F, 0x0706);
    }
    else if ((0 == strcmp(sBaudRateInfo, "100KBPS")) || (0 == strcmp(sBaudRateInfo, "100K")))
    {
        iError = CanChEnable(0);
        iError = ChangeCanChBaudRate(0, 0x0F, 0x070A);
    }
    else if ((0 == strcmp(sBaudRateInfo, "40KBPS")) || (0 == strcmp(sBaudRateInfo, "40K")))
    {
        iError = CanChEnable(0);
        iError = ChangeCanChBaudRate(0, 0x63, 0x0203);
    }
    else if ((0 == strcmp(sBaudRateInfo, "20KBPS")) || (0 == strcmp(sBaudRateInfo, "20K")))
    {
        iError = CanChEnable(0);
        iError = ChangeCanChBaudRate(0, 0x63, 0x0706);
    }
    else if ((0 == strcmp(sBaudRateInfo, "10KBPS")) || (0 == strcmp(sBaudRateInfo, "10K")))
    {
        iError = CanChEnable(0);
        iError = ChangeCanChBaudRate(0, 0x7F, 0x070F);
    }
    else
    {
        iError = -51;
    }
    return iError;
}
