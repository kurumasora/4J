#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>



int recursive_sum(int *v,int n, int *count){
    
        
    if(n==1){
        return v[0];
    }else{
        int *A1,*A2;

        int left = (int)floor(n/2.0);
        int right = n - left;
        A1 = (int*)malloc(left * sizeof(int));
        A2 = (int*)malloc(right * sizeof(int));        
           
        memcpy(A1, &v[0], left * sizeof(int));
        memcpy(A2, &v[left], right * sizeof(int));
        
        
    
        int x = recursive_sum(A1, left, count);
        int y = recursive_sum(A2, right, count);

        free(A1);
        free(A2);

       

        (*count) ++;

        return x + y;

    }
   

  
}

int main(){
    int n=0;
   
    int count = 0;

    scanf("%d",&n);
    
    int *v = (int *)malloc(n * sizeof(int));

    if(v==NULL){
        return 1;
    }else{
        for(int i = 0; i<n; i++){
            scanf("%d",&v[i]);
        }
    }

    printf("%d\n", recursive_sum(v,n,&count));

    printf("%d\n",count);

    free(v);

    return 0;


   



}