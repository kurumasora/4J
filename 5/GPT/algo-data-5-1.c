
#include "node.h"
#include "bfs.h"

int main(void)
{
    /* 木を構築 */
    Node *root = build_sample_tree();

    /* 横型探索を実行 */
    bfs(root);

    return 0;
}
