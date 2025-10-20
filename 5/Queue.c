
#include <stdio.h>
#include <stdlib.h>
#include "./includes/Queue.h"
#include "./includes/Node.h"

int initQueue(Queue *q, int max) {
    q->num = q->front = q->rear = 0;//初期化
    if ((q->que = calloc(max, sizeof(Node))) == NULL) {//calloc(動的に確保するメモリの数,sizeof(型名))==何もない（失敗）
        q->max = 0;
        return -1;//失敗
    }
    q->max = max;
    return 0;
}

int Enque(Queue *q, Node *n){
    if (q->num >= q->max){//今ある要素数 >= 最大要素数 　->　満杯　->　追加できない
        return -1;//失敗
    } else {
        q->que[q->rear] = *n;//次にデータを入れる場所に構造体を指し示す*nを代入
        q->num++;//要素数を増やす
        q->rear++;//次の場所を一つ進める
    }
    if (q->rear == q->max){ //配列の端っこまで来たら
        q->rear = 0;//前の方の要素はすでに取り出されて空いているかもしれないので、先頭に戻って再利用する
    }
    return 0;
}

Node *Deque(Queue *q){//操作対象
    if (q->num <= 0){
        return NULL;
    } else {
        q->num--;//要素数を減らす
        if (q->front == q->max){//フロントが配列の末尾に来たら
            q->front = 0;
        }
        return &q->que[q->front++];//フロントの次のノードにアクセスしそれを取り出す。
    }
}

void Clear(Queue *q) { 
    q->num = q->front = q->rear = 0; 
}

void terminateQueue(Queue *q) {
    if (q->que != NULL) {
        free(q->que);
    }
    q->max = q->num = q->front = q->rear = 0;
}
