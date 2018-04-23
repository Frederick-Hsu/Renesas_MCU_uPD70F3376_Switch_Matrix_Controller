/****************************************************************************************
 * File name    : CAN_Control.h
 * Description  : Configure some CAN settings in this CAN module.
 * Creator      : Frederick Hsu
 * Creation date: Sun.  09 April, 2018
 * Copyright(C) 2018    All rights reserved.
 *
 ****************************************************************************************/

#ifndef CAN_CONTROL_H
#define CAN_CONTROL_H
    
    typedef enum GetMode
    {
        IMMEDIATE = 0,
        CACHE = 1
    }
    CanGetMode_t;
    
    int Set_CAN_BaudRate(char sBaudRateInfo[]);
    int Set_CAN_ReceiveMode(char sModeInfo[]);
    
    CanGetMode_t Retrieve_CAN_ReceiveMode(void);
    
    int CAN0_GetAllTelegram(void);
    int CAN0_GetLatestTelegram(void);

#endif  /* CAN_CONTROL_H */
