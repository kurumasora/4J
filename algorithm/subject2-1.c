#include<stdio.h>

void triple(int x[10000], int n){
    int t=0;
    for(int i = 0; i < n; i++){
        t = x[i] /3;
    }
    if (n[0]==0){
        printf("YES\n");
    }else{
        printf("NO\n");

    }
}

void sum(int x, int n){
    
    int sum = 0;
    for(int i =0; i<n; i++){
        sum += n[i];
    }
}

int main(){
    int n;
    int x;
    scanf("%d", &n);
    
    triple(x,n);

    sum(x,n);

   
    return 0;
}


