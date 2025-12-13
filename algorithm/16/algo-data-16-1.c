#include <stdio.h>
#include <stdlib.h>

static int* buff;
long long mc = 0; // 交換回数（反転数）

static void __mergesort(int a[], int left, int right){
    if (left < right){
        int center = (left + right) / 2;
        int p = 0;          // buff にコピーした要素数
        int i;              // 右側（a の center+1 から right）の読み取り位置
        int j = 0;          // buff の読み取り位置
        int k = left;       // マージ結果を書き戻す a の位置（最初は left）

        __mergesort(a, left, center);
        __mergesort(a, center + 1, right);

        // 左側を buff に退避
        for (i = left; i <= center; i++){
            buff[p++] = a[i];
        }
        i = center + 1; // 右側の開始位置を明示

        // 左側(buff) と 右側(a) をマージ
        while (i <= right && j < p){
            if (buff[j] <= a[i]){
                a[k++] = buff[j++];
            } else {
                a[k++] = a[i++];
                mc += (p - j); // 右側要素が先 → 左側残数分の交換が必要
            }
        }
        // 左側の残りをコピー（右側の残りは既に正しい位置にある）
        while (j < p){
            a[k++] = buff[j++];
        }
    }
}

int Mergesort(int a[], int n){
    buff = (int*)calloc(n, sizeof(int));
    if (buff == NULL) return -1;
    __mergesort(a, 0, n - 1);
    free(buff);
    return 0;
}

int main(void){
    int n = 0;
    if (scanf("%d", &n) != 1 || n < 0) return 0;

    int* value = (int*)calloc(n, sizeof(int));
    if (!value) return 0;

    for (int i = 0; i < n; i++){
        scanf("%d", &value[i]);
    }

    mc = 0;                 // 交換回数リセット
    if (Mergesort(value, n) != 0){
        free(value);
        return 0;
    }

    // 結果出力（必要なら配列も出力）
    for (int i = 0; i < n; i++){
        if (i) printf(" ");
        printf("%d", value[i]);
    }
    printf("\n");
    printf("%lld\n", mc);   // 交換回数を表示

    free(value);
    return 0;
}