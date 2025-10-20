
#include <stdio.h>
#include <stdlib.h>
#include "./includes/Tree.h"
#include "./includes/Queue.h"

static void setinit(Node *n){
	n->data = 50;//root

	add(n, 21);
	add(n, 65);

	Node *p1 = &n->child[0];
	add(p1, 10);
	add(p1, 14);
	add(p1, 18);

	Node *p2 = &p1->child[0];
	add(p2, 5);
	add(p2, 8);
	add(p2, 53);

	Node *p3 = &p2->child[0];
	add(p3, 2);
	add(p3, 3);

	Node *p4 = &p3->child[0];
	add(p4, 1);
	add(p4, 84);
	add(p4, 68);

	Node *p5 = &p1->child[1];
	add(p5, 12);
	add(p5, 13);

	Node *p6 = &p1->child[2];
	add(p6, 16);
	add(p6, 19);

	Node *p7 = &n->child[1];
	add(p7, 55);
	add(p7, 60);
	add(p7, 63);

	Node *p8 = &p7->child[0]; 
	add(p8, 52);
	add(p8, 54);

	Node *p9 = &p7->child[1]; 
	add(p9, 57);
	add(p9, 59);

	Node *p10 = &p7->child[2]; 
	add(p10, 64);

}

void add(Node *n, int x){//木構造のノード n に、新しい子ノード（値 x をもつ）を追加する関数です。
	n->child = realloc(n->child, (n->count+1)*sizeof(Node));//realloc は「メモリのサイズを変更する関数」,子ノードの要素数を増やし子ノードを再定義
	if (n->child == NULL){
		exit(EXIT_FAILURE);
	}
	n->child[n->count].data = x;
	n->child[n->count].count = 0;
	n->child[n->count].child = NULL;

	n->count++;
}

void initTree(Node *n){
	n->count = 0;
	n->child = malloc(sizeof(Node));
	setinit(n);
}

void terminateTree(Node *n){
	if (n->count != 0){
		for (int i=0; i<n->count; i++){
			terminateTree(&n->child[i]);
		}
	} else {
		free(n->child);
	}
}
