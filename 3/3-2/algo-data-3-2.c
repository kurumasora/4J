#include <stdio.h>
#include <stdlib.h>
#include "IntQueue.h"

#define MAX_SIZE 10000

int main(void) {
    IntQueue que;
    int op, v;
    
    if (Initialize(&que, MAX_SIZE) == -1) {
        puts("キューの生成に失敗しました。");
        return 1;
    }

    while (op != 11) {
        scanf("%d", &op);

        if (op == 1) {
            scanf("%d", &v);
            Enque(&que, v);
            printf("op1: Enque_%d\n", v);
        } else if (op == 2) {
            Deque(&que, &v);
            printf("op2: Deque_%d\n", v);
        } else if (op == 3) {
            Peek(&que, &v);
            printf("op3: Peek_%d\n", v);
        } else if (op == 4) {
            Print(&que);
            printf("op4: Print executed\n");
        } else if (op == 5) {
            Clear(&que);
            printf("op5: Clear_%d\n", Size(&que));
        } else if (op == 6) {
            printf("op6: Capacity_%d\n", Capacity(&que));
        } else if (op == 7) {
            printf("op7: Size_%d\n", Size(&que));
        } else if (op == 8) {
            printf("op8: IsEmpty_%d\n", IsEmpty(&que));
        } else if (op == 9) {
            printf("op9: IsFull_%d\n", IsFull(&que));
        } else if (op == 10) {
            scanf("%d", &v);
            printf("op10: Search_%d\n", Search(&que, v));
        } else if (op == 11) {
            printf("op11: Exit executed\n");
            return 0;
        }
    }
    return 0;
}