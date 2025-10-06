
#include <stdio.h>
#include <stdlib.h>
#include "IntQueue.h"

int Initialize(IntQueue *q, int max)
{
    q->num = q->front = q->rear = 0;
    q->que = calloc(max, sizeof(int));
    if (q->que == NULL)
    {
        q->max = 0;
        return -1;
    }
    q->max = max;
    return 0;
}

int Enque(IntQueue *q, int value)
{

    if (q->num >= q->max)
    {
        return -1;
    }
    else
    {
        q->num++;
        q->que[q->rear++] = value;
        if (q->rear == q->max)
        {
            q->rear = 0;
        }
        return 0;
    }
}

int Deque(IntQueue *q, int *value)
{
    if (q->num <= 0)
    {
        return -1;
    }
    else
    {
        q->num--;
        *value = q->que[q->front++];
        if (q->front == q->max)
        {
            q->front = 0;
        }
        return 0;
    }
}

int Peek(const IntQueue *q, int *value)
{
    if (q->num <= 0)
    {
        return -1;
    }
    *value = q->que[q->front];
    return 0;
}

void Print(const IntQueue *q)
{
    printf("\n");
    for (int i = q->front; i < q->num; i++)
    {
        printf("%d\n", q->que[i]);
    }
}

void Clear(IntQueue *q)
{
    q->num = 0;
    q->front = 0;
    q->rear = 0;
}

int Capacity(const IntQueue *q)
{
   return q->max;
}

int Size(const IntQueue *q)
{
   return q->num;
}

int IsEmpty(const IntQueue *q)
{
    if (q->num == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int IsFull(const IntQueue *q)
{
    if (q->num == q->max)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Search(const IntQueue *q, int value)
{
    for (int i = q->front; i < q->num; i++)
    {
        if (q->que[i] == value)
        {
            return i;
        }
    }
    return -1;
}

void Terminate(IntQueue *q)
{
    if (q->que != NULL)
    {
        free(q->que);
    }
    q->max = 0;
    q->num = 0;
    q->rear = 0;
    q -> front = 0;
}
