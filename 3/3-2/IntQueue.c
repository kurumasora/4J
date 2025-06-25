
#include <stdio.h>
#include <stdlib.h>
#include "IntQueue.h"

int Initialize(IntQueue *q, int max) {
    q->num = q->front = q->rear = 0;
    if ((q->que = calloc(max, sizeof(int))) == NULL) {
        q->max = 0;
        return -1;
    }
    q->max = max;
    return 0;
}

int Enque(IntQueue *q, int value) {
    if (q->num >= q->max)
        return -1;
    q->num++;
    q->que[q->rear++] = value;
    if (q->rear == q->max)
        q->rear = 0;
    return 0;
}

int Deque(IntQueue *q, int *value) {
    if (q->num <= 0)
        return -1;
    q->num--;
    *value = q->que[q->front++];
    if (q->front == q->max)
        q->front = 0;
    return 0;
}

int Peek(const IntQueue *q, int *value) {
    if (q->num <= 0)
        return -1;
    *value = q->que[q->front];
    return 0;
}

void Print(const IntQueue *q) {
    for (int i = 0; i < q->num; i++) {
        printf("%d\n", q->que[(q->front + i) % q->max]);
    }
}

void Clear(IntQueue *q) {
    q->num = q->front = q->rear = 0;
    printf("%d\n", Size(q));
}

int Capacity(const IntQueue *q) {
    return q->max;
}

int Size(const IntQueue *q) {
    return q->num;
}

int IsEmpty(const IntQueue *q) {
    return q->num <= 0;
}

int IsFull(const IntQueue *q) {
    return q->num >= q->max;
}

int Search(const IntQueue *q, int value) {
    for (int i = 0; i < q->num; i++) {
        if (q->que[(q->front + i) % q->max] == value)
            return i + 1;  // 1-based index
    }
    return -1;
}

void Terminate(IntQueue *q) {
    if (q->que != NULL)
        free(q->que);
    q->max = q->num = q->front = q->rear = 0;
}