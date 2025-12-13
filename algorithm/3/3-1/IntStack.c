#include <stdio.h>
#include <stdlib.h>
#include "IntStack.h"

int Initialize(IntStack *s, int max)
{
    s->ptr = 0;
    s->stk = calloc(max, sizeof(int)); // stkをint型で要素数max個で配列を動的に確保（要素は０で埋められる）
    if (s->stk == NULL)
    {
        s->max = 0;
        return -1;
    }
    s->max = max;
    return 0;
}

int Push(IntStack *s, int value)
{
    if (s->ptr >= s->max)
    { // 満杯だったら
        return -1;
    }
    s->stk[s->ptr++] = value; // インクリメント(入れる)
    return 0;
}

int Pop(IntStack *s, int *value)
{
    if (s->ptr <= 0)
    { // 空だったら
        return -1;
    }
    *value = s->stk[--s->ptr]; // デクリメント（取り出す）
    return 0;
}

int Peek(const IntStack *s, int *value)
{ // スタックを順番に表示
    // データの出し入れがないのでconst
     if (s->ptr <= 0)
        {
            return -1;
        }
    
        *value = s->stk[s->ptr - 1];

    return 0;
}

void Print(const IntStack *s){
    for (int i = 0; i < s->ptr; i++){
        printf("%d\n", s->stk[(s->ptr-1)-i]);
    }
}

void Clear(IntStack *s){
    s->ptr = 0;
}

int Capacity(const IntStack *s){
    return s->max;
}

int Size(const IntStack *s){
    return s->ptr;
}

int IsEmpty(const IntStack *s){
    if(s->ptr <= 0){
        return 1;
    }else{
        return 0;
    }
}

int IsFull(const IntStack *s){
    if(s->ptr == s->max){
        return 1;
    }else{
        return 0;
    }
}

int Search(const IntStack *s, int value){
    for(int i = 0; i < s->ptr; i++){
        int judge = s->stk[(s->ptr-1)-i];
        if(judge == value){
            return i;
        }
    }
    return -1;
}

void Terminate(IntStack *s){
    if(s->stk != NULL){
        free(s->stk);
    }
    s->max = s->ptr = 0;
}




