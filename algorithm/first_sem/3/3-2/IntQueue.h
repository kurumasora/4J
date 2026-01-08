// int型キューIntQueue（ヘッダ部）

#ifndef ___algo_data_3_2
#define ___algo_data_3_2

//--- キューを実現する構造体 ---//
typedef struct {
    int max;    // キューの容量
    int num;    // 現在のデータ数
    int front;  // 先頭要素カーソル（最も古い）
    int rear;   // 末尾要素カーソル（最も新しい）
    int *que;   // キュー本体（の先頭）（実際に要素を格納する配列ポインタ）
} IntQueue;

//--- キューの初期化 ---//
int Initialize(IntQueue *q, int max);

//--- キューにデータをエンキュー ---//
int Enque(IntQueue *q, int value);

//--- キューからデータをデキュー ---//
int Deque(IntQueue *q, int *value);

//--- キューからデータをピーク ---//
int Peek(const IntQueue *q, int *value);

//--- 全データを削除 ---//
void Clear(IntQueue *q);

//--- キューの容量 ---//
int Capacity(const IntQueue *q);

//--- キューのデータ数 ---//
int Size(const IntQueue *q);

//--- キューは空か ---//
int IsEmpty(const IntQueue *q);

//--- キューは満杯か ---//
int IsFull(const IntQueue *q);

//--- キューからの探索 ---//
int Search(const IntQueue *q, int value);

//--- 全データの表示 ---//
void Print(const IntQueue *q);

//--- キューの後始末 ---//
void Terminate(IntQueue *q);

#endif
