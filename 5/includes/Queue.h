
#pragma once
#include "Node.h"

typedef struct {
    int max;//キューの最大数
    int num;//キューの要素数
    int front;//キューの先頭データの場所
    int rear;//次にデータを入れる場所
    Node *que;//ノード型配列。実際のデータを格納する
} Queue;

int initQueue(Queue *q, int max);
int Enque(Queue *q, Node *n);
Node *Deque(Queue *q);
void Clear(Queue *q);
void terminateQueue(Queue *q);
