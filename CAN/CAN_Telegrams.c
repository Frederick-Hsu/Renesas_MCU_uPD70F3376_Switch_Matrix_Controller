/**************************************************************************************************
 * File name    : CAN_Telegrams.c
 * Description  : Implement the CAN telegram queue manipulation functions.
 * Creator      : Frederick Hsu
 * Creation date: Sun.  22 April, 2018
 * Copyright(C) 2018    All rights reserved.
 *
 **************************************************************************************************/

#include "CAN_Telegrams.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CanTelegramQueue_t CreateInitTelegramQueue(void)
{
    CanTelegramQueue_t queue;
    queue.head = (PtrTelegramNode_t)malloc(sizeof(TelegramNode_t));
    if (queue.head == NULL)
    {
        queue.head = NULL;
        queue.tail = NULL;
        queue.length = 0;
    }
    queue.tail = queue.head;
    (queue.head)->next = NULL;
    queue.length = 0;
    
    return queue;
}

Status_t IsTelegramQueueEmpty(CanTelegramQueue_t queue)
{
    if (queue.head->next == NULL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int TelegramQueueLength(CanTelegramQueue_t queue)
{
    int len = 0;
    PtrTelegramNode_t pNode = queue.head;
    while (pNode != queue.tail)
    {
        len++;
        pNode = pNode->next;
    }
    return len;
}

Status_t EnTelegramQueue(CanTelegramQueue_t *queue, Telegram telegram)
{
    PtrTelegramNode_t pNewNode, pNode;
    if (queue->length >= MAX_QUEUE_LENGTH)  /* At this scenario, you should dequeue one node */
    {
        pNode = queue->head->next;
        queue->head->next = pNode->next;
        free(pNode);
        queue->length--;
    }
    
    pNewNode = (PtrTelegramNode_t)malloc(sizeof(TelegramNode_t));
    if (pNewNode == NULL)
    {
        return FALSE;
    }
    sprintf(pNewNode->content, "%s", telegram);
    pNewNode->next = NULL;
    
    (queue->tail)->next = pNewNode;
    queue->tail = pNewNode;
    queue->length++;
    return TRUE;
}

Status_t DeTelegramQueue(CanTelegramQueue_t *queue, Telegram *telegram)
{
    PtrTelegramNode_t pNode;
    if (queue->head == queue->tail)     /* This scenario shows that the queue is empty */
    {
        return FALSE;
    }
    pNode = (queue->head)->next;
    sprintf(telegram, "%s", pNode->content);
    queue->head->next = pNode->next;
    if (queue->tail == pNode)
    {
        queue->tail = queue->head;
    }
    free(pNode);
    queue->length--;
    return TRUE;
}

Status_t ReadTelegramFromTail(CanTelegramQueue_t queue, unsigned int count)
{
    unsigned int startIndex, n;
    PtrTelegramNode_t pStartNode = queue.head;
    Telegram telegram = {0x00};
    
    if ((count > queue.length) || (count == 0))
    {
        return FALSE;
    }
    startIndex = queue.length - count;
    for (n = 1; n <= startIndex; n++)
    {
        pStartNode = pStartNode->next;
    }
    
    for (n = 1; n <= count; n++)
    {
        sprintf(telegram, "%s", pStartNode->content);
        UARTD2_SendData(telegram, strlen(telegram));
        pStartNode = pStartNode->next;
    }
    return TRUE;
}

/**************************************************************************************************
 * END OF FILE 
 **************************************************************************************************/
