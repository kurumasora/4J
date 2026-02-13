#include <stdio.h>

/* 指定された制約に基づき最大値を定義 [cite: 3, 4] */
#define MAX_N 50
#define MAX_C 100

/* 2つの整数のうち大きい方を返す関数 */
int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n, C;
    int v[MAX_N], w[MAX_N];
    int id;
    int dp[MAX_C + 1];

    /* 入力読み込み [cite: 8, 9, 10, 11] */
    if (scanf("%d", &n) != 1) return 1;
    if (scanf("%d", &C) != 1) return 1;

    for (int i = 0; i < n; i++) {
        /* 荷物番号、価値、重さの順に読み込む [cite: 12, 13, 14] */
        if (scanf("%d %d %d", &id, &v[i], &w[i]) != 3) break;
    }

    /* 動的計画法（DP）による計算 */
    /* dp[j] は容量 j における価値の最大値を保持する */
    for (int j = 0; j <= C; j++) {
        dp[j] = 0;
    }

    for (int i = 0; i < n; i++) {
        /* 同じ荷物を重複して選ばないよう、容量を後ろから更新する (0-1ナップサック) */
        for (int j = C; j >= w[i]; j--) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }

    /* 結果の出力 [cite: 16, 17] */
    printf("%d\n", dp[C]);

    return 0;
}