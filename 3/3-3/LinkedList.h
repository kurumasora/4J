#ifndef __LinkedList
#define __LinkedList

typedef struct __node{
    int data;//データそのもの
    struct __node *next;//次のノードのポインタ(次のノードの構造体全体にアクセスしたい)
    //↑自己参照構造体：https://daeudaeu.com/c-self-relation/
} Node;

typedef struct {
    Node *head;//先頭ノードに該当するアドレスを格納
    Node *crnt;//現在注目しているノードに該当するアドレスを格納
    int n;//リストの要素数（識別番号//）
} List;


void initialize(List *l);
void insertFront(List *l, const int value);//1
void insertRear(List *l, const int value);//2
void removeFront(List *l);//3
void removeRear(List *l);//4
Node *search(List *l, const int value, int *n, Node **pre);
int removeSearch(List *l, const int value);//5
int searchIndex(List *l, const int value);//6
int size(List *l);//7
void clear(List *l);//
void print(const List *l);
void terminate(List *l);

#endif