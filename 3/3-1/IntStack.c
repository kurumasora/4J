#include<stdio.h>
#include<stdlib.h>
#include"IntStack.h"

int Initialize(IntStack *s, int max){
    s->ptr = 0;//スタックの要素数を０にする
    if((s->stk = calloc(max,sizeof(int)))==NULL){//calloc を使って、max 個の int サイズのメモリを確保。
        s->max=0;//失敗したら(NULL)最大容量を0にする
        return -1;//-1でエラー通知
    }
    s->max=max;
    return 0;
    
}

int Push(IntStack *s, int v){
    s->stk[s->ptr]=v;
    s->ptr++;//入力してインクリメント
    return 0;
}

int Pop(IntStack *s, int *v){
    s->ptr--;//デクリメントしてから代入
    *v = s->stk[s->ptr];
    return 0;
}

int Peek(const IntStack *s, int *v){
    *v = s->stk[s->ptr-1];
    return 0;
}

void Print(const IntStack *s){
    for(int i = s->ptr-1; i>=0;i--){
        printf("%d",s->stk[i]);
    }
    printf("\n");
}

void Clear(IntStack *s){
    s->ptr=0;
    
}

int Capacity(IntStack *s){
   return s->max;
}

int Size(IntStack *s){
    return s->ptr;
}

int IsEmpty(const IntStack *s){
   return s->ptr <= 0;
}

int IsFull(const IntStack *s){
    return s->ptr >= s->max;
}

int Search(const IntStack *s, int v){//ピークから探索
    for(int i = s->ptr-1; i>=0; i--){
        if(v==s->stk[i]){
           return i;
        }
    }
    return -1;//探索失敗
}

void Terminate(IntStack *s){
    if(s->stk!=NULL){
        free(s->stk);
    }
    s->max = s->ptr = 0;
}