// オープンアドレス法によるハッシュ（ソース部）

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "Bucket.h"
#include "ClosedHash.h"

/*--- ハッシュ関数（keyのハッシュ値を返す） ---*/
static int hash(int key, int size)
{
  return key % size;
}

/*--- 再ハッシュ関数 ---*/
static int rehash(int key, int size)
{
  return (key + 1) % size;
}

/*--- ノードの各メンバに値を設定 ----*/
static void SetBucket(Bucket* n, const int *v, Status stat)
{
 n->v = *v;     // データをコピー
 n->stat = stat; // 状態を設定
}

/*--- ハッシュ表を初期化 ---*/
int Initialize(ClosedHash* h, int size)
{
  if ((h->table = calloc(size, sizeof(Bucket))) == NULL) {
		h->size = 0;
		return 0;
	}

	h->size = size;
	for (int i = 0; i < size; i++)		// すべてのバケットを空にする
		h->table[i].stat = Empty;		
	return 1;
}

/*--- 探索 ---*/
Bucket* Search(const ClosedHash* h, const int* x)
{
  int key = hash(*x, h->size);  //探索するデータのハッシュ値
  Bucket* p = &h->table[key];			// 着目ノード

  for (int i = 0; p->stat != Empty && i < h->size; i++) {
    if (p->stat == Occupied && p->v == *x)
			return p;
		key = rehash(key, h->size);		// 再ハッシュ
		p = &h->table[key];
  }
  
  return NULL;
}

/*--- データの追加 ---*/
int Add(ClosedHash* h, const int* x)
{
  int key = hash(*x, h->size);		// 追加するデータのハッシュ値
	
  Bucket* p = &h->table[key];			// 着目ノード

  if (Search(h, x))					
		return 1;		                 // このキーは登録ずみ
  
  for (int i = 0; i < h->size; i++) {
    if (p->stat == Empty || p->stat == Deleted) {
			SetBucket(p, x, Occupied);
			return 0;
		}
		key = rehash(key, h->size);		// 再ハッシュ
		p = &h->table[key];
    }
    return 2;                     //ハッシュ表が満杯
}

/*--- データの削除 ---*/
int Remove(ClosedHash* h, const int* x)
{
  Bucket *p = Search(h, x);
  if(p == NULL){
    return 1;						// そのキー値は存在しない
  }

  p->stat = Deleted;
  return 0;
}

/*--- ハッシュ表をダンプ ---*/
void Dump(const ClosedHash* h)
{
  for (int i = 0; i < h->size; i++) {
    printf("%05d : ", i);

    if (h->table[i].stat == Occupied) {
      printf("%d\n", h->table[i].v);
    } else if(h->table[i].stat == Empty) {
      printf("Unregistered\n");
    } else {
      printf("Deleted\n");
    }
  }
}

/*--- 全データの削除 ---*/
void Clear(ClosedHash* h)
{
  for (int i = 0; i < h->size ; i++) {	// すべてのバケットを
    h->table[i].stat = Empty;		// 空にする
  }
}

/*--- ハッシュ表を後始末 ---*/
void Terminate(ClosedHash* h)
{
  Clear(h);				// 全データを削除
  free(h->table);		// ハッシュ表用配列の記憶域を解放
  h->size = 0;			// ハッシュ表の容量をクリア
}
