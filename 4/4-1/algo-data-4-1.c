#include<stdio.h>
#define MAX_HEIGHT 10
#define MAX_NODES ((1<<MAX_HEIGHT)-1)//2^h-1(節の数、左シフト演算でべき乗計算)

void binary_tree(int height,int tree[],int nodes){
    int count = 1;
    int level;//現在の木の深さ

    for(level=1;level<=height;level++){
        int current_nodes = 1<<(level-1);//2^(level-1)で現在のレベルでの節の数
        printf("%d:",level);
        int j;

        for(j=0;j<current_nodes;j++){
            if (count>nodes){
                break;
            }
            printf("%d",tree[count]);
            count++;
        }
        printf("\n");

    }
    
}

int main(){
    int h;
    int n;
    int t[MAX_NODES];
    int i;

    printf("height of tree:");
    scanf("%d",&h);
    
    n = (1<<h)-1;

    printf("node of tree\n");
    for(i=1;i<=n;i++){
        printf("→");
        scanf("%d",&t[i]);
    }


    binary_tree(h,t,n);


    
    return 0;
}