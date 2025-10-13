
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

///@param *n　見つかった位置のアドレスを格納
///@param **pre 見つかったノードの直前のノードのアドレスを格納
Node *search(List *l, const int x, int *n, Node **pre){//**preはmain関数の参照渡しのremovesearchの参照わたし
    Node *ptr = l->head;
    *n = 1;
    *pre = NULL;//先頭ノードの前にはノードがないため初期化
    while (ptr != NULL){
        if (ptr->data == x){//データが一致すれば
            l->crnt = ptr; //現在注目ノードとして更新
            return ptr;//データが一致したノードのアドレスを返す
        }
        *pre = ptr;
        ptr = ptr->next;
        (*n)++;//*nなのは、別の関数で値を返すから
    }
    *n = -1;//見つからなかったという印
    *pre = NULL;//直前ノードもnull
    return NULL;
}

int removeSearch(List *l, const int x){
    int ___n;
    Node *pre;
    Node *ptr = search(l, x, &___n, &pre);//この関数では使用しないため&___n（アンダーバーをつける）
    if (ptr == NULL){
        return -1;//該当ノードなし
    }
    if (pre == NULL) {//先頭ノードだった場合(search関数でpreはNullと初期化されている)
        l->head = ptr->next;
    } else {
        pre->next = ptr->next;//preのnextはptrのnextつまりptrはとばされる
    }
    free(ptr);
    l->crnt = pre;
    return 1;
}

int searchIndex(List *l, const int x){
    int n;
    Node *___pre, *___ptr;
    ___ptr = search(l, x, &n, &___pre);
    if (___ptr == NULL){
        return -1;
    }
    return n;
}

int size(List *l){
    return l->n;
}

void clear(List *l){
    while (l->head != NULL){
        removeFront(l);
    }
    l->crnt = NULL;
}

void print(const List *l){
    if (l->head == NULL){
        
    } else {
        Node *ptr = l->head;
        while (ptr != NULL) {
            printf("%d\n", ptr->data);
            ptr = ptr->next;
        }
    }
}

void terminate(List *l){
    clear(l);
}