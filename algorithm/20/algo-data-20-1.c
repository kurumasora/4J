#include <stdio.h>

#define MAX_N 100

int main(void) {
    int n;
    int adj[MAX_N][MAX_N];
    int i, j;

    // 頂点数の入力
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "入力エラー：頂点数を読み込めませんでした．\n");
        return 1;
    }

    if (n <= 0 || n > MAX_N) {
        fprintf(stderr, "頂点数が範囲外です．(1〜%d)\n", MAX_N);
        return 1;
    }

    // 隣接行列の入力
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (scanf("%d", &adj[i][j]) != 1) {
                fprintf(stderr, "入力エラー：隣接行列を読み込めませんでした．\n");
                return 1;
            }
        }
    }

    // 各頂点の次数を計算
    int degree[MAX_N];
    for (i = 0; i < n; i++) {
        degree[i] = 0;
        for (j = 0; j < n; j++) {
            degree[i] += adj[i][j];
        }
    }

    // 奇数次数の頂点数を数える
    int odd_count = 0;
    for (i = 0; i < n; i++) {
        if (degree[i] % 2 != 0) {
            odd_count++;
        }
    }

    // 一筆書きの可能性判定
    // 連結であることは入力条件として仮定されている
    if (odd_count == 0 || odd_count == 2) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}
