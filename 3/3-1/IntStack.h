#ifndef ___IntStack
#define ___IntStack



typedef struct{
    int max;//スタックの最大容量=10000
    int ptr;//スタックの現在の位置
    int *stk;//スタックの先頭アドレスを格納するためのポインタ変数
} IntStack;

//初期化//
int Initialize(IntStack *s, int max);
//1:プッシュ//
int Push(IntStack *s, int v);
//2:ポップ//
int Pop(IntStack *s, int *v);
//3:ピーク//
int Peek(const IntStack *s, int *v);
//4:全表示（ピーク(頂上)から）//
void Print(const IntStack *s);
//5:スタックを空にし、データの個数を出力（７）//
void Clear(IntStack *s);
//6:最大容量を出力//
int Capacity(IntStack *s);
//7:データの個数//
int Size(IntStack *s);
//8:空なら1、そうでないなら0を出力//
int IsEmpty(const IntStack *s);
//9:満杯なら1、そうでないなら0を出力//
int IsFull(const IntStack *s);
//10:数値が見つかればピークからの位置を返す、みつからなければ-1//
int Search(const  IntStack *s, int v);
//11:後始末//
void Terminate(IntStack *s);

#endif