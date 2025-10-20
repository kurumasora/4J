
/*横型探索ではキューの概念が必要。
  
    先に発見した順に処理する」必要があるため、
    FIFO（先入れ先出し）が本質です。これを実現するのがキューです。


*/

#include <stdio.h>
#include "./includes/Tree.h"
#include "./includes/Queue.h"
#define CAPACITY 16384

void discover(Node *n, Queue *q){    
    int count = 1;
    while (q->num != 0){
        Node *tmp = Deque(q);
        printf("%d %d\n", count++, tmp->data);
        for (int i=0; i<tmp->count; i++){
            Enque(q, &tmp->child[i]);
        }
    }
}

int main(void){
    Queue q; 
    Node n;
    initQueue(&q, CAPACITY);
    initTree(&n);

    Enque(&q, &n);
    discover(&n, &q);

    terminateQueue(&q);
    terminateTree(&n);
    return 0;
}
