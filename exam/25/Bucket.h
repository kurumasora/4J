// Buecket（ヘッダ部）

#ifndef ___Bucket
#define ___Bucket

/*--- 要素の状態 ---*/
typedef enum {
  Occupied, Empty, Deleted
} Status;

/*--- 要素 ---*/
typedef struct {
  int v;		// データ
  Status stat;		// 要素の状態
} Bucket;

int BucketCmp(const Bucket* x, const Bucket* y);

void PrintBucket(const Bucket* x);

void PrintLnBucket(const Bucket* x);

Bucket ScanBucket();

#endif

