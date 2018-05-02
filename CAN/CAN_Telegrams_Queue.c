/**************************************************************************************************
 * File name    : can_telegrams_queue.c
 * Description  : Implement the queue manipulation to manage CAN telegrams.
 * Creator      : Frederick Hsu
 * Creation date: Wed.  25 April, 2018
 * Copyright(C) 2018    All rights reserved.
 *
 **************************************************************************************************/

#include "can_telegrams_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status_t InitTelegramsQueue(TelegramsQueue_t *queue, Telegram telegram)
{
    queue->head = (PtrTelegramNode_t)malloc(sizeof(TelegramNode_t));
    if (queue->head == NULL)
    {
        queue->head = NULL;
        queue->tail = NULL;
        queue->length = 0;
        return FALSE;
    }
    sprintf(queue->head->content, "%s", telegram);
    #if defined (TEST_PURPOSE)
        queue->head->indicator = 1;
    #endif
    queue->head->next = NULL;

    queue->tail = queue->head;
    queue->length = 1;
    return TRUE;
}

TelegramsQueue_t CreateAndInitTelegramsQueue(Telegram oneTelegram)
{
    TelegramsQueue_t queue;
    queue.head = (PtrTelegramNode_t)malloc(sizeof(TelegramNode_t));
    if (queue.head == NULL)
    {
        queue.head = NULL;
        queue.tail = NULL;
        queue.length = 0;
        return queue;
    }
    sprintf(queue.head->content, "%s", oneTelegram);
#if defined (TEST_PURPOSE)
    queue.head->indicator = 1;
#endif
    queue.head->next = NULL;

    queue.tail = queue.head;
    queue.length = 1;

    return queue;
}

Status_t IsTelegramsQueueEmpty(TelegramsQueue_t queue)
{
    if (queue.length <= 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

unsigned int LengthOfTelegramsQueue(TelegramsQueue_t queue)
{
    unsigned int length = 0;
    PtrTelegramNode_t pNode = queue.head;

    while (pNode != NULL)
    {
        length++;
        pNode = pNode->next;
    }
    return length;
}

Status_t EnTelegramsQueue(TelegramsQueue_t *queue, Telegram newTelegram)
{
    PtrTelegramNode_t pNewNode, pNode;
    if (queue->length >= MAX_QUEUE_SIZE)
    {
        /* Need to dequeue the head node at this scenario */
        pNode = queue->head;
        queue->head = pNode->next;
        free(pNode);
        queue->length--;
    }

    pNewNode = (PtrTelegramNode_t)malloc(sizeof(TelegramNode_t));
    if (pNewNode == NULL)
    {
        return FALSE;
    }
    sprintf(pNewNode->content, "%s", newTelegram);
#if defined (TEST_PURPOSE)
    pNewNode->indicator = queue->length + 1;
#endif
    pNewNode->next = NULL;

    queue->tail->next = pNewNode;
    queue->tail = pNewNode;
    queue->length++;
    return TRUE;
}

Status_t DeTelegramsQueue(TelegramsQueue_t *queue, 
    Telegram discardedTelegram
#if defined (TEST_PURPOSE)
    , int *discardedIndicator
#endif
)
{
    PtrTelegramNode_t pDiscardedNode;
    if (queue->length <= 0)
    {
        return FALSE;
    }
    pDiscardedNode = queue->head;
    queue->head = pDiscardedNode->next;
    sprintf(discardedTelegram, "%s", pDiscardedNode->content);
#if defined (TEST_PURPOSE)
    *discardedIndicator = pDiscardedNode->indicator;
#endif
    free(pDiscardedNode);

    queue->length--;
    return TRUE;
}

Status_t DestroyTelegramsQueue(TelegramsQueue_t *queue)
{
    PtrTelegramNode_t pNode = queue->head, pTempNode;
    while (pNode != NULL)
    {
        pTempNode = pNode;
        pNode = pNode->next;
        free(pTempNode);
        queue->length--;
    }

    queue->head->next = NULL;
    queue->head = NULL;
    queue->tail = queue->head;
    return TRUE;
}

Status_t GetHeadNodeOfTelegramsQueue(TelegramsQueue_t queue, Telegram telegramContent)
{
    PtrTelegramNode_t pNode;
    if (queue.length <= 0)
    {
        return ERROR;
    }
    pNode = queue.head;
    sprintf(telegramContent, "%s", pNode->content);
    return TRUE;
}

Status_t GetTailNodeOfTelegramsQueue(TelegramsQueue_t queue, Telegram telegramContent)
{
    PtrTelegramNode_t pNode;
    if (queue.length <= 0)
    {
        return ERROR;
    }
    pNode = queue.tail;
    sprintf(telegramContent, "%s", pNode->content);
    return TRUE;
}

void TraverseTelegramsQueue(TelegramsQueue_t *queue, void (*access)(Telegram))
{
    PtrTelegramNode_t pNode = queue->head;
    while (pNode != NULL)
    {
        access(pNode->content);
        pNode = pNode->next;
    }
}

Status_t ReverselyFetchItemsFromTelegramsQueue(TelegramsQueue_t queue,
                                               unsigned int count,
                                               void (*fetch)(Telegram))
{
    unsigned int startIndex;
    unsigned int index = count;
    PtrTelegramNode_t pStartNode;
    Telegram *items = (Telegram *)malloc(count * sizeof(Telegram));

    if (count > (unsigned)queue.length)
    {
        free(items);
        return ERROR;
    }

    pStartNode = queue.head;    /* From the head node to traverse */
    for (startIndex = 1; startIndex <= (queue.length-count); startIndex++)
    {
        pStartNode = pStartNode->next;
    }
    
    while (pStartNode != NULL)
    {
        sprintf(*(items + (index - 1)), "%s", pStartNode->content);
        index--;
        pStartNode = pStartNode->next;
    }

    for (index = 0; index < count; index++)
    {
        fetch(*(items + index));
    }
    free(items);

    return TRUE;
}

void DisplayTelegramsQueue(TelegramsQueue_t queue)
{
    PtrTelegramNode_t pNode = queue.head;
    int index = 1;
    
    printf("\n\n\nQueue start address : 0x%016llX\n\n", (unsigned long long)(&queue));
    printf("Head address  : 0x%016llX\n", (unsigned long long)queue.head);
    printf("    content   : address = 0x%016llX,    value = %s\n", (unsigned long long)&(queue.head->content), queue.head->content);
#if defined (TEST_PURPOSE)
    printf("    indicator : address = 0x%016llX,    value = %d\n", (unsigned long long)&(queue.head->indicator), queue.head->indicator);
#endif
    printf("    next      : address = 0x%016llX\n", (unsigned long long)queue.head->next);
    printf("==========================================================================================================\n\n");

    while (pNode != NULL)
    {
        printf("Node %d address: 0x%016llX\n", index, (unsigned long long)pNode);
        printf("    content    : address = 0x%016llX,    value = %s\n", (unsigned long long)&(pNode->content), pNode->content);
#if defined (TEST_PURPOSE)
        printf("    indicator  : address = 0x%016llX,    value = %d\n", (unsigned long long)&(pNode->indicator), pNode->indicator);
#endif
        printf("    next       : address = 0x%016llX\n", (unsigned long long)pNode->next);
        printf("==========================================================================================================\n\n");

        index++;
        pNode = pNode->next;
    }

    printf("Tail address  : 0x%016llX\n", (unsigned long long)queue.tail);
    printf("    content   : address = 0x%016llX,    value = %s\n", (unsigned long long)&(queue.tail->content), queue.tail->content);
#if defined (TEST_PURPOSE)
    printf("    indicator : address = 0x%016llX,    value = %d\n", (unsigned long long)&(queue.tail->indicator), queue.tail->indicator);
#endif
    printf("    next      : address = 0x%016llX\n", (unsigned long long)queue.tail->next);
    printf("==========================================================================================================\n\n");

    printf("Queue length  : %d\n", queue.length);
    return;
}


