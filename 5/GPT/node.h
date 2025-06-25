#ifndef NODE_H
#define NODE_H

#define MAX_CHILDREN 10

typedef struct Node {
    int id;
    int child_count;
    struct Node *children[MAX_CHILDREN];
} Node;

/* ノード生成と追加 */
Node *create_node(int id);
void   add_child(Node *parent, Node *child);

/* サンプル木を構築してルートを返す */
Node *build_sample_tree(void);

#endif /* NODE_H */
