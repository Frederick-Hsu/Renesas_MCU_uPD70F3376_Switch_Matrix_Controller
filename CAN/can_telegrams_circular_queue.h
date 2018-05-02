/**************************************************************************************************
 * File name    : can_telegrams_circular_queue.h
 * Description  : Define a circular queue to store CAN telegrams, declare the manipulation function
 *              : prototypes, based on the circular queue structure.
 * Creator      : Frederick Hsu
 * Creation date: Tue.  01 May 2018
 * Copyright(C) 2018    All rights reserved.
 *
 **************************************************************************************************/

#ifndef CAN_TELEGRAMS_CIRCULAR_QUEUE_H
#define CAN_TELEGRAMS_CIRCULAR_QUEUE_H

    #include "general.h"

    #define MAX_LENGTH_OF_ONE_TELEGRAM      36
    #define MAX_CIRCULAR_QUEUE_SIZE         10

    #define TETEGRAM_ARRAY_TYPE1    1
    #define TELEGRAM_ARRAY_TYPE2    2
    #define TELEGRAM_ARRAY_TYPE     TELEGRAM_ARRAY_TYPE2

    typedef char                   Telegram[MAX_LENGTH_OF_ONE_TELEGRAM];

    typedef struct TelegramsCircularQueue
    {
#if (TELEGRAM_ARRAY_TYPE == TELEGRAM_ARRAY_TYPE1)
        Telegram *container;
#elif (TELEGRAM_ARRAY_TYPE == TELEGRAM_ARRAY_TYPE2)
        Telegram  container[MAX_CIRCULAR_QUEUE_SIZE];
#endif
        int headIndex;
        int tailIndex;
        unsigned int actualQueueSize;
    }
    TelegramsCircularQueue_t,   *PtrTelegramsCircularQueue_t;

    Status InitTelegramsCircularQueue(TelegramsCircularQueue_t *queue);
    void   EnqueueIntoTelegramsCircularQueue(TelegramsCircularQueue_t *queue, Telegram oneTelegram);
    Status DequeueFromTelegramsCircularQueue(TelegramsCircularQueue_t *queue, Telegram outTelegram);
    int LengthOfTelegramsCircularQueue(TelegramsCircularQueue_t queue);
    Status IsTelegramsCircularQueueEmpty(TelegramsCircularQueue_t queue);
    void DestroyTelegramsCircularQueue(TelegramsCircularQueue_t *queue);
    void TraverseTelegramsCircularQueue(TelegramsCircularQueue_t queue, void (*access)(Telegram));
    Status ReverselyFetchTelegrams(TelegramsCircularQueue_t queue, int count, void (*fetch)(Telegram));

    void DisplayTelegramCircularQueue(TelegramsCircularQueue_t queue);

#endif  /* CAN_TELEGRAMS_CIRCULAR_QUEUE_H */
