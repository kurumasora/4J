
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

static Node *allocNode(void){//新規ノード作成
    return calloc(1, sizeof(Node));
}

static void setNode(Node *n, int x, Node *next){//setNode(ノードを作る場所、値、次のノードのアドレス)
    n->data = x;//データそのものを格納
    n->next = next;//次のノードのアドレスを格納
}


void initialize(List *l){
    l->head = NULL;
    l->crnt = NULL;
    l->n = 0;
}

void insertFront(List *l, const int x){
    Node *ptr = l->head;            //挿入前の先頭ノードのアドレスを*ptrに格納
    l->head = l->crnt = allocNode();//ノードを新しく作り、先頭ノードを更新。また、現在のノードも更新
    setNode(l->head, x, ptr);//先頭ノードにxの値を作り、ptrをnextにする
    l->n++;//要素数を追加
}

void insertRear(List *l, const int x){
    if (l->head == NULL){//リストが空なら
        insertFront(l, x);//先頭に配置
    } else {
        Node *ptr = l->head;//headのアドレスをptrとする
        while (ptr->next != NULL){//nextがnullでない間は
            ptr = ptr->next;        //nextがnullのノードまで検索
            //ptrにptrの次の情報を代入->headのアドレスを末尾に移動させている
        }
        ptr->next = l->crnt = allocNode();
        setNode(ptr->next, x, NULL);
        l->n++;
    }
}

void removeFront(List *l){
    if (l->head != NULL){
        Node *ptr = l->head->next;//今の先頭ノードを消去するため、その次のノードをptrに一時保存
        free(l->head);//元々の先頭ノードのメモリを解放
        l->head = l->crnt = ptr;//新しい先頭ノードとしてptrにセット。同時にcrntも更新
    }
    l->n--;//要素数を減らす
}

void removeRear(List *l){
    if (l->head->next == NULL){//headの次のノードがnullなら(リスト上にノードが一個だけ存在)
        removeFront(l);
    } else {
        Node *ptr = l->head;
        Node *pre;//末尾から二番目のノード

        while (ptr->next != NULL){//nextがnullを指さない間
            pre = ptr;//preはptrとなる
            ptr = ptr->next;//ptrはptrの次のノードとなる。
        }//これでpreはptrの一個前のノードとなる
        pre->next = NULL;//preの次、ptrのノードのリンクを切る
        free(ptr);//メモリ解放
        l->crnt = pre;//preは末尾ノードとなる
    }
    l->n--;
}
///@param *n　見つかった位置のアドレスを格納
///@param **pre 見つかったノードの直前のノードのアドレスを格納
Node *search(List *l, const int x, int *n, Node **pre){
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
    Node *ptr = search(l, x, &___n, &pre);
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
