#include<stdio.h>

int binary_search(int n, int k, int d[]){
    int left = 0;
    int right = n-1;
    int mid = (left + right)/2;
    while(left <= right){
        if(d[mid] == k){
            return mid;
        }else if(d[mid] > k){
            right = mid - 1;
            mid = (left + right)/2;
        }else if(d[mid] < k){
            left = mid + 1;
            mid = (left + right)/2;
        }
    }
    return -1;
}


int main(){
    int n = 0;
    int d[10000];
    int k = 0;
    printf("n?:");
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &d[i]);
    }
    printf("k?:");
    scanf("%d", &k);


    int result = binary_search(n, k, d);
    
    if(result != -1){
        printf("Found:%d %d\n", result, k);
    }else if(result == -1){
        printf("Not Found:%d\n", k);
    }
    return 0;

}
