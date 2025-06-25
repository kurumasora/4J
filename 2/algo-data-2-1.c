#include<stdio.h>

int main(){
    int num=0;
    int count=0;
    int sum = 0;
    scanf("%d", &num);
    printf("\n");
    int temp = num;
    if(num>0){
        while(num>0){
        num /= 10;
        count++;
        }
    

    }else{
        printf("\n");
        return 0; 
    }
   
    while(count > 0){
        sum += temp % 10;
        temp /= 10;
        count--;
    }
    

    printf("%d\n", sum);

    printf("\n");
   
    for(int i=0; i<count; i++){
       num/=3;
    }
    if (num==0){
        printf("YES\n");
    }else{
        printf("NO\n");
    }

    
    
    
   

   
    return 0;
}


