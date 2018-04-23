/**************************************************************************************************
 * File name    : CAN_Telegrams.h
 * Description  : Define the CAN telegram queue structure.
 * Creator      : Frederick Hsu
 * Creation date: Sun.  22 April, 2018
 * Copyright(C) 2018    All rights reserved.
 *
 **************************************************************************************************/

#ifndef CAN_TELEGRAMS_H
#define CAN_TELEGRAMS_H

    #define MAX_QUEUE_LENGTH    10
    typedef unsigned char       Telegram[36];
    
    typedef enum Status
    {
        FALSE = 0,
        TRUE = 1
    }
    Status_t;
    
    typedef struct TelegramNode
    {
        Telegram content;
        struct TelegramNode *next;
    }
    TelegramNode_t, *PtrTelegramNode_t;
    
    typedef struct CanTelegramQueue
    {
        PtrTelegramNode_t head;
        PtrTelegramNode_t tail;
        int length;
    }
    CanTelegramQueue_t, *PtrCanTelegramQueue_t;
    
    CanTelegramQueue_t CreateInitTelegramQueue(void);
    Status_t IsTelegramQueueEmpty(CanTelegramQueue_t queue);
    int TelegramQueueLength(CanTelegramQueue_t queue);
    Status_t EnTelegramQueue(CanTelegramQueue_t *queue, Telegram telegram);
    Status_t DeTelegramQueue(CanTelegramQueue_t *queue, Telegram *telegram);
    Status_t ReadTelegramFromTail(CanTelegramQueue_t queue, unsigned int count);

#endif  /* CAN_TELEGRAMS_H */
