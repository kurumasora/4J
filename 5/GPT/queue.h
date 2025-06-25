#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

#define QUEUE_CAPACITY 100

typedef struct {
    Node *data[QUEUE_CAPACITY];
    int   front;
    int   rear;
} Queue;

/* キュー操作 */
void init_queue(Queue *q);
int  is_empty(const Queue *q);
void enqueue(Queue *q, Node *value);
Node *dequeue(Queue *q);

#endif /* QUEUE_H */
