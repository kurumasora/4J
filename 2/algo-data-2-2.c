#include <stdio.h>

#define BALL_WEIGHT 100

// 与えられたボール集合の合計を求める
int sum_of_balls(int balls[], int identify[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += balls[identify[i]];
    }
    return sum;
}

// 集合の合計値を表示する
void print_current_sum(int balls[], int identify[], int size) {
    int sum = sum_of_balls(balls, identify, size);
    printf("不良品を含む集合の合計: %d\n", sum);
}

// 不良品を探す
void find_defective_ball(int balls[], int num) {
    int id[num];
    for (int i = 0; i < num; i++) {
        id[i] = i;
    }

    // 最初に全体の合計を計算
    int total_sum = sum_of_balls(balls, id, num);
    printf("分割前のボールの合計: %d\n", total_sum);

    int expected_sum = num * BALL_WEIGHT;  // 正常なら期待される合計
    int diff = total_sum - expected_sum;   // 正常との差分

    int size = num;

    while (size > 1) {
        int mid = size / 2;

        int sum_first_half = sum_of_balls(balls, id, mid);
        int expected_first_half = mid * BALL_WEIGHT;
        int diff_first_half = sum_first_half - expected_first_half;

        // diffと同じ符号なら不良品は前半にいる
        if ((diff > 0 && diff_first_half > 0) || (diff < 0 && diff_first_half < 0)) {
            size = mid;
        } else {
            // 後半にいるのでidを後半に更新
            for (int i = 0; i < size - mid; i++) {
                id[i] = id[mid + i];
            }
            size = size - mid;
        }

        print_current_sum(balls, id, size);
    }

    // 出力順を「重さ→番号」に変更
    printf("不良品の重さ: %d\n", balls[id[0]]);
    printf("不良品のボール番号: %d\n", id[0]+1);
}

int main() {
    int num = 0;
    int balls[100];
    scanf("%d", &num);

    for (int i = 0; i < num; i++) {
        scanf("%d", &balls[i]);
    }

    find_defective_ball(balls, num);

    return 0;
}
