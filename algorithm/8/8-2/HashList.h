#pragma once

typedef enum {
	Occupied,
	Empty,
	Deleted
} Status;

typedef struct {
	int data;
	Status stat;//要素の状態
} Bucket;

typedef struct {
	int size;
	Bucket *table;//ハッシュ表の先頭要素へのポインタ
} HashList;

int Initialize(HashList *h, int size);
Bucket *Search(const HashList *h, const int x);
int Add(HashList *h, const int x);
int Remove(HashList *h, const int x);
void Dump(const HashList *h);
void Clear(HashList *h);
void Terminate(HashList *h);
