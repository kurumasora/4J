/*DFSにおけるpreOder,inOder, postOderの違い

３つの走査の違いはどのタイミングで親ノードに立ち寄るか。

          A
         /  \
        B    C

preOder : A->B->C(親→左子→右子)
inOder  : B->A->C(左子→親→右子)
postOder: B->C->A(左子→右子→親)

=>実装では再帰関数を使い、３つの走査を実現する

printfするタイミングを変えるだけで３つの走査を変えることができる

preorder :親ノードを子に降りる前にprintfで出力
inorder  :親ノードを左子の再帰の後、右子の再帰の前に出力
postorder:親ノードを左右の再帰の後に出力



child[0]:左子ノード、child[1]:右子ノード



*/


#include <stdio.h>
#include "Queue.h"
#include "Tree.h"
#define CAPACITY 16384
int _recursiveCounter = 1;

void discover(Node *n, const int mode) {
    if (n == NULL) {
        return;
    }

    if (mode == 1){//preorder
        printf("%d %d\n", _recursiveCounter++, n->data);

    }
    
    if (n->count >= 1) {//子ノードは一つ以上->左子ノード走査
        discover(&n->child[0], mode);
    }

    if (mode == 2){//inorder
        printf("%d %d\n", _recursiveCounter++, n->data);
    }

    if (n->count >= 2) {//子ノードは２つ以上->右子ノード走査
        discover(&n->child[1], mode);
    }

    if (mode == 3){//postorder
        printf("%d %d\n", _recursiveCounter++, n->data);
    }
}

int main(void) {
    Queue q;
    Node n;
    int mode;
    initQueue(&q, CAPACITY);
    initTree(&n);

    Enque(&q, &n);

    printf("what mode do you choose? (preorder:1, inorder:2, postorder:3)");

    scanf("%d", &mode);
    if (mode == 1){
        printf("preOrder\n");
    } else if (mode == 2){
        printf("inOrder\n");
    } else if (mode == 3){
        printf("postOrder\n");
    }

    discover(&n, mode);

    terminateQueue(&q);
    terminateTree(&n);
    return 0;
}