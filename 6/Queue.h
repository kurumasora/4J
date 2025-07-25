#pragma once
#include "Node.h"

typedef struct {
    int max;
    int num;
    int front;
    int rear;
    Node *que;
} Queue;

int initQueue(Queue *q, int max);
int Enque(Queue *q, Node *n);
Node *Deque(Queue *q);
void Clear(Queue *q);
void terminateQueue(Queue *q);
