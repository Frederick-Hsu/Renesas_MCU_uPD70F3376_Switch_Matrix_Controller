/**************************************************************************************************
 * File name    : can_telegrams_circular_queue.c
 * Description  : Implement the manipulation functions, based on the CAN Telegrams circular queue.
 * Creator      : Frederick Hsu
 * Creation date: Tue.  01 May 2018
 * Copyright(C) 2018    All rights reserved.
 *
 **************************************************************************************************/

#include "can_telegrams_circular_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status InitTelegramsCircularQueue(TelegramsCircularQueue_t *queue)
{
#if (TELEGRAM_ARRAY_TYPE == TELEGRAM_ARRAY_TYPE1)
    int row = 0;
    
    queue->container = (Telegram *)malloc(MAX_CIRCULAR_QUEUE_SIZE * sizeof(Telegram));
    // queue->container = (Telegram *)malloc(MAX_CIRCULAR_QUEUE_SIZE);
    if (queue->container == NULL)
    {
        return ERROR;
    }
    /* Empty this container, it is actually an array[36][10] */
    for (row = 0; row < MAX_CIRCULAR_QUEUE_SIZE; row++)
    {
        memset((queue->container)[row], 0, sizeof(Telegram));
    }
    queue->headIndex = 0;
    queue->tailIndex = 0;
    queue->actualQueueSize = 0;
    
    return OK;
#elif (TELEGRAM_ARRAY_TYPE == TELEGRAM_ARRAY_TYPE2)
    int row = 0;
    for (row = 0; row < MAX_CIRCULAR_QUEUE_SIZE; row++)
    {
        memset(queue->container[row], 0, sizeof(Telegram));
    }
    queue->headIndex = 0;
    queue->tailIndex = 0;
    queue->actualQueueSize = 0;
    return OK;
#endif
}

void EnqueueIntoTelegramsCircularQueue(TelegramsCircularQueue_t *queue, Telegram oneTelegram)
{
    if ( ((queue->tailIndex + 1) % MAX_CIRCULAR_QUEUE_SIZE) == queue->headIndex )   /* The queue is full */
    {
        /* Move the head index */
        queue->headIndex = (queue->headIndex + 1) % MAX_CIRCULAR_QUEUE_SIZE;
        if (queue->actualQueueSize == MAX_CIRCULAR_QUEUE_SIZE)
        {
            queue->actualQueueSize--;   /* Equivalent to push out one item from the circular queue */
        }
    }
    sprintf((queue->container)[queue->tailIndex], "%s", oneTelegram);
    
    queue->tailIndex = (queue->tailIndex + 1) % MAX_CIRCULAR_QUEUE_SIZE;
    queue->actualQueueSize++;
}

Status DequeueFromTelegramsCircularQueue(TelegramsCircularQueue_t *queue, Telegram outTelegram)
{
    if (queue->headIndex == queue->tailIndex)       /* Queue is empty */
    {
        return ERROR;
    }
    sprintf(outTelegram, "%s", (queue->container)[queue->headIndex]);
    queue->headIndex = (queue->headIndex + 1) % MAX_CIRCULAR_QUEUE_SIZE;
    queue->actualQueueSize--;
    return OK;
}

int LengthOfTelegramsCircularQueue(TelegramsCircularQueue_t queue)
{
    return queue.actualQueueSize;
}

Status IsTelegramsCircularQueueEmpty(TelegramsCircularQueue_t queue)
{
    if (queue.headIndex == queue.tailIndex)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void DestroyTelegramsCircularQueue(TelegramsCircularQueue_t *queue)
{
#if (TELEGRAM_ARRAY_TYPE == TELEGRAM_ARRAY_TYPE1)
    if (queue->container)
    {
        free(queue->container);
    }
    queue->container = NULL;
    queue->headIndex = 0;
    queue->tailIndex = 0;
    queue->actualQueueSize = 0;
#elif (TELEGRAM_ARRAY_TYPE == TELEGRAM_ARRAY_TYPE2)
    int row = 0;
    for (row = 0; row < MAX_CIRCULAR_QUEUE_SIZE; row++)
    {
        memset(queue->container[row], 0, sizeof(Telegram));
    }
    queue->headIndex = 0;
    queue->tailIndex = 0;
    queue->actualQueueSize = 0;
#endif
}

void TraverseTelegramsCircularQueue(TelegramsCircularQueue_t queue, void (*access)(Telegram))
{
    int startIndex = queue.headIndex;
    
    while (startIndex != queue.tailIndex)
    {
        access((queue.container)[startIndex]);
        startIndex = (startIndex + 1) % MAX_CIRCULAR_QUEUE_SIZE;
    }
}

Status ReverselyFetchTelegrams(TelegramsCircularQueue_t queue, int count, void (*fetch)(Telegram))
{
    unsigned int startIndex, index = 0;
    if (count > queue.actualQueueSize)
    {
        return ERROR;
    }
    
    if (queue.tailIndex == 0)
    {
        startIndex = MAX_CIRCULAR_QUEUE_SIZE-1;
    }
    else
    {
        startIndex = (queue.tailIndex-1) % MAX_CIRCULAR_QUEUE_SIZE;
    }
    
    for (index = 0; index < count; index++)
    {
        fetch(queue.container[startIndex]);
        if (startIndex == 0)
        {
            startIndex = MAX_CIRCULAR_QUEUE_SIZE-1;     /* Reset */
        }
        else
        {
            startIndex--;
        }
    }
    return OK;
}

void DisplayTelegramCircularQueue(TelegramsCircularQueue_t queue)
{
    int length = queue.actualQueueSize, startIndex = 0;
    
    printf("Telegrams circular queue : \n");
    for (startIndex = 0; startIndex < length; startIndex++)
    {
        printf("    telegram[%d] = %s\n", startIndex, queue.container[startIndex]);
    }
    printf("    head index = %d\n", queue.headIndex);
    printf("    tail index = %d\n", queue.tailIndex);
    printf("    actual queue size = %d\n", queue.actualQueueSize);
    printf("=======================================================================================\n\n");
}
