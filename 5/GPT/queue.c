
#include <stdio.h>
#include <stddef.h>
#include "queue.h"

/* 初期化 */
void init_queue(Queue *q)
{
    q->front = 0;
    q->rear  = 0;
}

/* 空判定 */
int is_empty(const Queue *q)
{
    return q->front == q->rear;
}

/* 追加 */
void enqueue(Queue *q, Node *value)
{
    if ((q->rear + 1) % QUEUE_CAPACITY != q->front) {
        q->data[q->rear] = value;
        q->rear          = (q->rear + 1) % QUEUE_CAPACITY;
    }
}

/* 取り出し */
Node *dequeue(Queue *q)
{
    Node *result = NULL;
    if (!is_empty(q)) {
        result   = q->data[q->front];
        q->front = (q->front + 1) % QUEUE_CAPACITY;
    }
    return result;
}
