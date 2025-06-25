#include <stdio.h>
#include "bfs.h"
#include "queue.h"

/* 幅優先探索を実行し，訪問順とノード番号を出力 */
void bfs(Node *root)
{
    if (root == NULL) {
        return;
    }

    Queue q;
    init_queue(&q);
    enqueue(&q, root);

    int order = 1;

    while (!is_empty(&q)) {
        Node *cur = dequeue(&q);
        printf("%d %d\n", order, cur->id);
        order++;

        for (int i = 0; i < cur->child_count; i++) {
            enqueue(&q, cur->children[i]);
        }
    }
}
