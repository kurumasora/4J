
#pragma once

typedef struct __node {
    int data;           //データ
    struct __node *left;//左子ノードへのポインタ
    struct __node *right;//右子ノードへのポインタ
} BinNode;

BinNode *search(BinNode *p, const int x);
BinNode *add (BinNode *p, const int x);
int removeNode(BinNode **root, const int x);
void printNode(const BinNode *p);
void freeTree(BinNode *p);
