#include <stdio.h>
#include <stdlib.h>

// 最大データ数 100000 
#define MAX_N 100000

// 配列の宣言（スタックオーバーフローを防ぐためグローバル領域またはヒープを使用推奨）
int A[MAX_N];
int temp[MAX_N]; // マージ操作用の一時配列

// マージ（併合）操作を行う関数
void merge(int left, int mid, int right) {
    int i = left;
    int j = mid;
    int k = left;

    // 左側と右側を比較しながら小さい順にtempへ格納
    while (i < mid && j < right) {
        if (A[i] <= A[j]) {
            temp[k++] = A[i++];
        } else {
            temp[k++] = A[j++];
        }
    }

    // 残りの要素をコピー
    while (i < mid) {
        temp[k++] = A[i++];
    }
    while (j < right) {
        temp[k++] = A[j++];
    }

    // 元の配列Aに書き戻し
    for (int l = left; l < right; l++) {
        A[l] = temp[l];
    }
}

// マージソートを行う再帰関数
// 範囲は [left, right) の半開区間
void merge_sort(int left, int right) {
    if (left + 1 < right) {
        int mid = (left + right) / 2;
        merge_sort(left, mid);
        merge_sort(mid, right);
        merge(left, mid, right);
    }
}

int main() {
    int n;

    // 1行目に整数nが与えられる [cite: 5, 6]
    if (scanf("%d", &n) != 1) {
        return 1; // 読み込みエラー
    }

    // データ数が最大値を超えないか確認（安全のため）
    if (n > MAX_N) {
        fprintf(stderr, "Data size exceeds MAX_N\n");
        return 1;
    }

    // 続けて1行に1個ずつ整数が与えられる [cite: 5, 7-9]
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    // マージソートの実行
    merge_sort(0, n);

    // 整列後の昇順に整数を出力する [cite: 11]
    // 出力形式に従い、v_0 から v_n-1 まで出力 [cite: 12-14]
    for (int i = 0; i < n; i++) {
        printf("%d\n", A[i]);
    }

    return 0;
}