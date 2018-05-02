/**************************************************************************************************
 * File name    : can_telegrams_queue.h
 * Description  : Define the queue structure to store CAN telegrams.
 * Creator      : Frederick Hsu
 * Creation date: Wed.  25 April, 2018
 * Copyright(C) 2018    All rights reserved.
 *
 **************************************************************************************************/

#ifndef CAN_TELEGRAMS_QUEUE_H
#define CAN_TELEGRAMS_QUEUE_H

    #include "general.h"

    #define MAX_QUEUE_SIZE      10
    #define TELEGRAM_LENGTH     36

    #define TEST_PURPOSE

    typedef unsigned char       Telegram[TELEGRAM_LENGTH];

    typedef struct TelegramNode
    {
        Telegram content;
        #if defined (TEST_PURPOSE)
            int indicator;
        #endif
        struct TelegramNode *next;
    }
    TelegramNode_t,     *PtrTelegramNode_t;

    typedef struct TelegramsQueue
    {
        PtrTelegramNode_t head;
        PtrTelegramNode_t tail;
        int length;
    }
    TelegramsQueue_t,   *PtrTelegramsQueue_t;

    Status_t InitTelegramsQueue(TelegramsQueue_t *queue, Telegram telegram);
    TelegramsQueue_t CreateAndInitTelegramsQueue(Telegram oneTelegram);
    Status_t IsTelegramsQueueEmpty(TelegramsQueue_t queue);
    unsigned int LengthOfTelegramsQueue(TelegramsQueue_t queue);
    Status_t EnTelegramsQueue(TelegramsQueue_t *queue, Telegram newTelegram);
    Status_t DeTelegramsQueue(TelegramsQueue_t *queue,
        Telegram discardedTelegram
    #if defined (TEST_PURPOSE)
        , int *discardedIndicator
    #endif
    );
    Status_t DestroyTelegramsQueue(TelegramsQueue_t *queue);
    Status_t GetHeadNodeOfTelegramsQueue(TelegramsQueue_t queue, Telegram telegramContent);
    Status_t GetTailNodeOfTelegramsQueue(TelegramsQueue_t queue, Telegram telegramContent);
    void TraverseTelegramsQueue(TelegramsQueue_t *queue, void (*access)(Telegram));
    Status_t ReverselyFetchItemsFromTelegramsQueue(TelegramsQueue_t queue,
                                                   unsigned int count,
                                                   void (*fetch)(Telegram));
    void DisplayTelegramsQueue(TelegramsQueue_t queue);

#endif  /* CAN_TELEGRAMS_QUEUE_H */
