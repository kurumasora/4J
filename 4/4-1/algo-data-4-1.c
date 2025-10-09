#include<stdio.h>
#define MAX_HEIGHT 10

int main(){
    int h;//
    int n = (1 << h)-1;//左ビットシフトで2^h-1が節の個数となる
    scanf("%d", &h);
    int tree[(1<<MAX_HEIGHT)-1] = {0};//1023個

    
    for(int i = 0; i < n; i++){
        scanf("%d", &tree[i]);
    }
    int count = 0;
    int start = 0;
    int print_level = 0;
    for(int i = 1; i <= n; i = i * 2){//配列をi*2個で区切って表示する
        count = i;
        printf("%d",print_level + 1);
        for(int j = 0; j < count; j++){
            printf("%d",tree[start + j]);
        }
        start += count;//表示の始まりの位置を更新する
        printf("\n");
        print_level++;
    }
}