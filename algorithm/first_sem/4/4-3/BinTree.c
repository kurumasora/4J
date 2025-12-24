#include <stdio.h>
#include <stdlib.h>
#include "BinTree.h"
/*
<2分探索木>

左部分木のノードのキー値は、そのノードのキー値より小さい
右部分木のノードのキー値は、そのノードのキー値より大きい

                11
            5       15
          4   7   13   18


→ 4, 5, 7, 11, 13, 15, 18


*/
static BinNode *allocBinNode(void){
    return calloc(1, sizeof(BinNode));
}

static void setBinNode(BinNode *n, const int x, BinNode *left, BinNode *right){
    n->data = x;
    n->left = left;
    n->right = right;
}

BinNode *search(BinNode *p, const int x){
    if (p == NULL){
        return NULL;//子にノードがないなら探索失敗
    } else if (p->data == x){
        return p;//着目ノードが目的とするノードと等しいなら探索成功
    } else if (p->data > x){
        search(p->left, x);
    } else {
        search(p->right, x);
    }
}



BinNode *add(BinNode *p, const int x){
    
    if (p == NULL){
        p = allocBinNode();
        setBinNode(p, x, NULL, NULL);//leftとrightがNULLであるということは、xのキー値をもつ根だけのノードを作成している
    } else if (p->data == x){
        return NULL;
    } else if (p->data > x){
        p->left = add(p->left, x);
    } else {
        p->right = add(p->right, x);
    }
    return p;
}

int removeNode(BinNode **root, const int x){
    BinNode *replacement, *temp;//tempは削除対象ノードを一時的に保持して free するために使われる
    //replacementは削除後にその場所へ繰り上げる置換ノード（例えば左部分木の最大ノード）を指すために使われます。
    BinNode **max;
    BinNode **link = root;

    while ((*link)->data != x){//消去する対象のノードがあるまで探索する
        if (*link == NULL){
            return -1;
        } else if ((*link)->data > x){
            link = &((*link)->left);
        } else {
            link = &((*link)->right);
        }
    }
    
    if ((*link)->left == NULL){//消去対象（親）の子ノードが一つだった場合
        replacement = (*link)->right;
    } else {                    //消去対象の子ノードが２つだった場合
        max = &((*link)->left);
        while ((*max)->right != NULL){
            max = &(*max)->right;             
        }
        replacement = *max;
        *max = (*max)->left;
        replacement->left = (*link)->left;
        replacement->right = (*link)->right;
    }

    temp = *link;
    *link = replacement;
    free(temp);

    return 0;
}

void printNode(const BinNode *p){
    if (p != NULL){
        printf("%d ", p->data);
        printNode(p->left);
        printNode(p->right);
    }
}

void freeTree(BinNode *p){
    if (p != NULL){
        freeTree(p->left);
        freeTree(p->right);
        free(p);
    }
}