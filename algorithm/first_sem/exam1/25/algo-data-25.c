
#include <stdio.h>
#include "ClosedHash.h"

int main(void)
{
    ClosedHash hash;
    Initialize(&hash, 10000);

    int v;
    int op = -1;

    while(op != 0){
        scanf("%d",&op);

        if(op == 1){
            scanf("%d", &v);
            printf("%d\n" ,Add(&hash, &v));
        }else if(op == 2){
            scanf("%d", &v);
            int result = Remove(&hash, &v);
            if(result != 0 ){
                printf("Not found\n");
            }
        }else if(op == 3){
            scanf("%d", &v);
            Bucket* p = Search(&hash, &v);
            if(p != NULL){
                printf("Found\n");
            }else{
                printf("Not Found\n");
            }
        }else if(op == 4){
            Clear(&hash);
        }else if(op == 5){
            Dump(&hash);
        }
    }
    Terminate(&hash);
}