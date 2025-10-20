#ifndef __LinkedList
#define __LinkedList

typedef struct __node{
    int data;
    struct __node *next;
} Node;

typedef struct {
    Node *head;//先頭ノードに該当するアドレスを格納
    Node *crnt;//現在注目しているノードに該当するアドレスを格納
    int n;//リストの要素数（識別番号//）
} List;


void initialize(List *l);
void insertFront(List *l, const int x);//1
void insertRear(List *l, const int x);//2
void removeFront(List *l);//3
void removeRear(List *l);//4
Node *search(List *l, const int x, int *n, Node **pre);
int removeSearch(List *l, const int x);//5
int searchIndex(List *l, const int x);//6
int size(List *l);//7
void clear(List *l);//
void print(const List *l);
void terminate(List *l);

#endif