// オープンアドレス法によるハッシュ（ヘッダ部）

#ifndef ___ClosedHash
#define ___ClosedHash

#include "Bucket.h"

/*--- ハッシュ表 ---*/
typedef struct {
  int     size;		// ハッシュ表の大きさ
  Bucket* table;		// ハッシュ表の先頭要素へのポインタ
} ClosedHash;

/*--- ハッシュ表を初期化 ---*/
int Initialize(ClosedHash* h, int size);

/*--- 探索 ---*/
Bucket* Search(const ClosedHash* h, const int* v);

/*--- データの追加 ---*/
int Add(ClosedHash* h, const int* x);

/*--- データの削除 ---*/
int Remove(ClosedHash* h, const int* x);

/*--- ハッシュ表をダンプ ---*/
void Dump(const ClosedHash* h);

/*--- 全データの削除 ---*/
void Clear(ClosedHash* h);

/*--- ハッシュ表を後始末 ---*/
void Terminate(ClosedHash* h);

#endif
