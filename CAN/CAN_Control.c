/****************************************************************************************
 * File name    : CAN_Control.c
 * Description  : Configure some CAN settings in this CAN module.
 * Creator      : Frederick Hsu
 * Creation date: Sun.  09 April, 2018
 * Copyright(C) 2018    All rights reserved.
 *
 ****************************************************************************************/


#include "CAN_Control.h"
#include <string.h>

#pragma ioreg

int Set_CAN_BaudRate(char sBaudRateInfo[])
{
    int iError = 0;
    if ((0 == strcmp(sBaudRateInfo, "1000KBPS")) || (0 == strcmp(sBaudRateInfo, "1000K")))
    {
        C0BRP = 0x01;
        C0BTR = 0x0706;
    }
    else if ((0 == strcmp(sBaudRateInfo, "500KBPS")) || (0 == strcmp(sBaudRateInfo, "500K")))
    {
        C0BRP = 0x03;
        C0BTR = 0x0706;
    }
    else if ((0 == strcmp(sBaudRateInfo, "250KBPS")) || (0 == strcmp(sBaudRateInfo, "250K")))
    {
        C0BRP = 0x0F;
        C0BTR = 0x0203;
    }
    else if ((0 == strcmp(sBaudRateInfo, "125KBPS")) || (0 == strcmp(sBaudRateInfo, "125K")))
    {
        C0BRP = 0x0F;
        C0BTR = 0x0706;
    }
    else if ((0 == strcmp(sBaudRateInfo, "100KBPS")) || (0 == strcmp(sBaudRateInfo, "100K")))
    {
        C0BRP = 0x0F;
        C0BTR = 0x070A;
    }
    else if ((0 == strcmp(sBaudRateInfo, "40KBPS")) || (0 == strcmp(sBaudRateInfo, "40K")))
    {
        C0BRP = 0x063;
        C0BTR = 0x0203;
    }
    else if ((0 == strcmp(sBaudRateInfo, "20KBPS")) || (0 == strcmp(sBaudRateInfo, "20K")))
    {
        C0BRP = 0x63;
        C0BTR = 0x0706;
    }
    else if ((0 == strcmp(sBaudRateInfo, "10KBPS")) || (0 == strcmp(sBaudRateInfo, "10K")))
    {
        C0BRP = 0x7F;
        C0BTR = 0x070F;
    }
    else
    {
        iError = -51;
    }
    return iError;
}
