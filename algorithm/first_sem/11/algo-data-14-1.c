#include <stdio.h>
#include <stdlib.h>

/* 
 * algo-data-14-1.c
 * 再帰関数と3要素分割（3-way partition）を用いたクイックソート実装．
 * 仕様：
 *  - 最大10000個の整数を整列．
 *  - switchは使わない．
 *  - 無限ループは使わない（繰り返し条件は明示）．
 *  - 単一文でも必ずブロック波括弧を付与．
 *  - quickとpartitionとswapの呼び出し回数を最後に出力．
 *
 * 入力：
 *   1行目：n
 *   2行目以降：n個の整数（空白または改行区切り）
 *
 * 出力：
 *   1行目：昇順に並べたn個の整数（空白区切り）
 *   2行目：quickの呼び出し回数
 *   3行目：partitionの呼び出し回数
 *   4行目：swapの呼び出し回数
 */

static long long g_quick_calls = 0;
static long long g_part_calls  = 0;
static long long g_swap_calls  = 0;
static long long g_sort3_calls = 0;

static void swap(int *a, int *b) {
    int tmp;
    if (a == b) {
        return;
    }
    g_swap_calls++;
    tmp = *a;
    *a  = *b;
    *b  = tmp;
}

/* 小区間（長さ1～3）を直接並べ替える */
static void sort3elem(int a[], int left, int right) {
    g_sort3_calls++;
    int len = right - left + 1;
    if (len <= 1) {
        return;
    }
    if (len == 2) {
        if (a[left] > a[right]) {
            swap(&a[left], &a[right]);
        }
        return;
    }
    /* len == 3 */
    int m = left + 1;
    if (a[left] > a[m]) {
        swap(&a[left], &a[m]);
    }
    if (a[m] > a[right]) {
        swap(&a[m], &a[right]);
    }
    if (a[left] > a[m]) {
        swap(&a[left], &a[m]);
    }
}

/* 3-way partition（Dijkstra）: [<pivot][=pivot][>pivot] に分割 */
static void partition3(int a[], int left, int right, int *out_lt_end, int *out_gt_begin) {
    g_part_calls++;

    /* ピボットは中央要素 */
    int mid = left + (right - left) / 2;
    int pivot = a[mid];
    /* 中央ピボットを先頭へ移す（実装都合） */
    swap(&a[left], &a[mid]);

    int lt = left;       /* a[left..lt-1] < pivot */
    int i  = left + 1;   /* 走査位置 */
    int gt = right;      /* a[gt+1..right] > pivot */

    while (i <= gt) {
        if (a[i] < pivot) {
            swap(&a[lt], &a[i]);
            lt++;
            i++;
        } else if (a[i] > pivot) {
            swap(&a[i], &a[gt]);
            gt--;
        } else {
            i++;
        }
    }
    *out_lt_end   = lt - 1;  /* <pivot の終端 */
    *out_gt_begin = gt + 1;  /* >pivot の開始 */
}

/* 再帰クイックソート（3-way partition使用） */
static void quick(int a[], int left, int right) {
    g_quick_calls++;
    if (left >= right) {
        return;
    }
    int len = right - left + 1;
    if (len <= 3) {
        sort3elem(a, left, right);
        return;
    }
    int lt_end, gt_begin;
    partition3(a, left, right, &lt_end, &gt_begin);

    if (left < lt_end) {
        quick(a, left, lt_end);
    }
    if (gt_begin < right) {
        quick(a, gt_begin, right);
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    if (n < 0) {
        n = 0;
    }
    if (n > 10000) {
        n = 10000;
    }

    int *a = (int*)malloc(sizeof(int) * (size_t)n);
    if (a == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            a[i] = 0;
        }
    }

    if (n > 1) {
        quick(a, 0, n - 1);
    }

    /* 整列結果 */
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", a[i]);
    }
    printf("\n");

    /* 呼び出し回数 */
    printf("%lld\n", g_quick_calls);
    printf("%lld\n", g_part_calls);
    printf("%lld\n", g_swap_calls);

    /* 必要ならsort3elem回数も出力：
       printf("%lld\n", g_sort3_calls);
     */

    free(a);
    return 0;
}
