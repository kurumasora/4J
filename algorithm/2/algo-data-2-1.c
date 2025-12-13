/*

1.1アルゴリズム:与えられた整数の各桁の総和が３で割り切れるなら、3の倍数である

整数nを入力

桁数を計算（while文）

桁数分だけfor文で計算する
    sumに整数を10で割ったあまりをインクリメント
    入力の整数を10でわり,更新する


*/



#include<stdio.h>

void calc_maltiple_of_three(int *number){
    int sum =  0;
    int temp = *number;
    int k = 0;          //桁数

    while(temp!=0){
        temp = temp/10;
        k++;
    }

    for (int i=0; i<k; i++ ){
        sum += *number % 10;
        *number = *number / 10;
    }

    printf("%d\n", sum);

    if(sum%3 == 0){
        printf("YES\n");
    }else{
        printf("NO\n");
    }
}

int main(){
    int n = 0;
    scanf("%d", &n);
    calc_maltiple_of_three(&n);
    return 0;
}
