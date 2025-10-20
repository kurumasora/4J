#include <stdio.h>
#include "Bucket.h"


int BucketCmp(const Bucket *x, const Bucket *y)
{
  if (x->v > y->v) {
    return 1;
  } else if (x->v == y->v) {
    return 0;
  } else {
    return -1;
  }
}


void PrintBucket(const Bucket *x)
{
  printf("%d", x->v);
}


void PrintLnBucket(const Bucket *x)
{
  printf("%d\n", x->v);
}

Bucket ScanBucket() {
  Bucket temp;

  scanf("%d", &temp.v );
  temp.stat = Occupied; // 入力されたので状態を「Occupied」に
  return temp;
}
