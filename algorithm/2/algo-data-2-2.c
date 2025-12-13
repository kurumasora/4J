#include <stdio.h>
#include <stdbool.h>

/*
①テニスボールを約半分ずつの２つの集合に分ける(B_1/B_2)

②B_1を秤にのせる

③B_1の重さが100の倍数->B_2に不良品がある
B_2の重さが100の倍数でない->B_1に不良品がある

不良品に含まれている集合に対し
    a, 1つのボールしかなければ、そのボールを不良品として、アルゴリズムを終了する
    b, 複数のボールが含まれていれば、①〜③を繰り返す。


*/

void divide_group_in_half(int ball[], int num)
{
    int len = num;
    int half = 0;
    int start = 0;
    int sum = 0;
    int order = 0;//不良品は何番目か？

    for (int i = 0; i < len; i++)
    {
        sum += ball[i];
    }
    printf("\n");
    printf("%d\n", sum);

    while (len > 1)
    {
        int sum_B1 = 0;
        int sum_B2 = 0;

        half = len / 2;

        for (int i = 0; i < half; i++)
        {
            sum_B1 += ball[start + i];
        }

        for (int i = 0; i < len - half; i++)
        {

            sum_B2 += ball[(start + half) + i];
    
        }

        

        if (sum_B1 % 100 == 0)
        {
            start = half;
            printf("%d\n", sum_B2);
            len = len - half;
            order = half;
        }

        else
        {
            printf("%d\n", sum_B1);
            len = len / 2;
            order = start;
        }

    }
    printf("%d\n", order+1);
}



int main()
{
    int n;
    scanf("%d", &n);

    int b[10000];

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &b[i]);
    }

    divide_group_in_half(b, n);

    return 0;
}

/*void ball_detect_if_even(int ball[], int *num)
{
    // sum, defective_sum(不良品が見つかるまで繰り返し), orderを出力したい
    int B1[5000];
    int B2[5000];

    int len = *num;

    int start = 0;
    int half = 0;

    int sum = 0;
    int defective_sum = 0;

    int order = 0;//どこに欠陥品があるか

    for (int i = 0; i < len; i++)
    {
        sum += ball[i];
    }
    printf("\n");
    printf("%d\n", sum);

    while (len > 1)//ボールが一個になると終了
    {

        int sum_B1 = 0;
        int sum_B2 = 0;

        half = len/2;

        for (int i = 0; i < len / 2; i++)
        {
            B1[i] = ball[i];
            sum_B1 += ball[i];
        }

        for (int i = 0; i < half; i++)
        {
            B2[i] = ball[half + i];
            sum_B2 += ball[half + i];
        }

        if (sum_B1 % 100 == 0)
        {
            defective_sum = sum_B2;
            printf("%d\n", sum_B2);
            start = half;
            order += half;
        }
        else if (sum_B1 % 100 != 0)
        {
            defective_sum = sum_B1;
            printf("%d\n", sum_B1);
            start = 0;
        }

        len /= 2;
        for(int i = 0; i < len; i++){
            ball[i] = ball[start + i];
        }

        if(len%2!=0){
            ball_detect_if_odd(ball, &len);
        }


    }


    printf("%d\n", order+1);

    // printf("%d\n", sum_B1);
    // printf("%d\n", sum_B2);
}


void ball_detect_if_odd(int ball[], int *num)
{
    int B1[5000];
    int B2[5000];

    int len = *num;

    int start = 0;
    int half = 0;

    int sum = 0;
    int defective_sum = 0;

    int order = 0;

    for (int i = 0; i < len; i++)
    {
        sum += ball[i];
    }
    printf("%d\n", sum);

    while (len > 1)
    {

        int sum_B1 = 0;
        int sum_B2 = 0;

        half = len/2;//奇数は切り捨て

        for (int i = 0; i < len / 2; i++)
        {
            B1[i] = ball[i];
            sum_B1 += ball[i];
        }

        for (int i = 0; i < len - half; i++)
        {
            B2[i] = ball[half+1 + i];
            sum_B2 += ball[half+1 + i];
        }

        if (sum_B1 % 100 == 0)
        {
            defective_sum = sum_B2;
            printf("%d\n", sum_B2);
            start = half;
            order += half;
        }
        else if (sum_B1 % 100 != 0)
        {
            defective_sum = sum_B1;
            printf("%d\n", sum_B1);
            start = 0;
        }

        len /= 2;
        for(int i = 0; i < len; i++){
            ball[i] = ball[start + i];
        }

        if(len%2!=0){
            ball_detect_if_even(ball, &len);
        }


    }
}*/
