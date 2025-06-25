
#include <stdlib.h>
#include "node.h"

/* ノードを生成して返す */
Node *create_node(int id)
{
    Node *n = (Node *)malloc(sizeof(Node));
    if (n != NULL) {
        n->id          = id;
        n->child_count = 0;
        for (int i = 0; i < MAX_CHILDREN; i++) {
            n->children[i] = NULL;
        }
    }
    return n;
}

/* 親に子を追加する */
void add_child(Node *parent, Node *child)
{
    if (parent->child_count < MAX_CHILDREN) {
        parent->children[parent->child_count++] = child;
    }
}

/* プログラム内で木を構築（高さ3，子数≤3の例）*/
Node *build_sample_tree(void)
{
    Node *n1 = create_node(1);
    Node *n2 = create_node(2);
    Node *n3 = create_node(3);
    Node *n4 = create_node(4);
    Node *n5 = create_node(5);
    Node *n6 = create_node(6);

    add_child(n1, n2);
    add_child(n1, n3);
    add_child(n1, n4);

    add_child(n2, n5);
    add_child(n2, n6);

    /* n3, n4 には子を付けない */

    return n1; /* ルートを返す */
}
