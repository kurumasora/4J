
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

// staticでこのファイル内のみで使える関数を生成
static Node *AllocNode(void)
{ // 要素一つのノードを生成
    return calloc(1, sizeof(Node));
}

// 作った一つのノードに対し、データそのものと次のノードのポインタを格納する
static void SetNode(Node *n, int value,  Node *next) //(どこに作るか, 代入する値, 次はどこか)
{
    n->data = value;
    n->next = next;
}

void initialize(List *list)
{
    list->head = NULL;
    list->crnt = NULL;
}

void insertFront(List *l, int value)
{
    Node *ptr = l->head;             // 変更前のノードにptrをおく
    l->head = l->crnt = AllocNode(); // 空のノード作成head,crnt更新
    SetNode(l->head, value, ptr);    // nextをptrにする
}

void insertRear(List *l, int value)
{
    if (l->head == NULL)
    {
        insertFront(l, value);
    }
    else
    {
        Node *ptr = l->head;
        while (ptr->next != NULL)
        { // 末尾ノードを見つけている
            ptr = ptr->next;
        }
        ptr->next = l->crnt = AllocNode();
        SetNode(ptr->next, value, NULL);
    }
}

void removeFront(List *l)
{
    if (l->head != NULL)
    {
        Node *ptr = l->head->next;
        free(l->head);
        l->head = l->crnt = ptr;
    }
}

void removeRear(List *l, int value)
{
    if (l->head == NULL)
    {
        removeFront(l);
    }else
    {
        Node *ptr = l->head;
        Node *pre;
        while (ptr->next != NULL)
        {
            pre = ptr;
            ptr = ptr->next;
        }
        pre->next = NULL;
        free(ptr);
        l->crnt = pre;
    }
}

