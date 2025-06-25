#include <stdio.h>

#define AMAX 10     // ★修正：年齢を10歳ごとに分けるためのグループ数（0～99歳を10分割）

//--- 身体検査データ型 ---//
typedef struct {
    char name[20];   // 氏名
    int height;      // 身長
    int age;         // ★修正：視力ではなく「年齢」に意味を明確化
} PhysCheck;

//--- 平均身長を求める関数 ---//
double ave_height(const PhysCheck dat[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += dat[i].height;
    return sum / n;
}

//--- 年齢分布（10歳刻み）を求める関数 ---//
void dist_vision(const PhysCheck dat[], int n, int dist[]) {
    for (int i = 0; i < AMAX; i++)
        dist[i] = 0;  // ★修正：配列を0で初期化

    for (int i = 0; i < n; i++) {
        int index = dat[i].age / 10;   // ★修正：年齢を10で割ってグループ番号を取得
        if (index >= 0 && index < AMAX)  // ★修正：範囲チェックを修正（10未満）
            dist[index]++;             // ★修正：その年齢グループに1人カウント
    }
}

int main(void) {
    PhysCheck x[] = {
        {"01 001", 162,  5},
        {"02 002", 142, 15},
        {"03 003", 132, 13},
        {"04 004", 152, 15},
        {"05 005", 162, 21},
        {"06 006", 172, 23},
        {"07 007", 182, 15},
        {"08 008", 192, 78},
        {"09 009", 161, 89},
        {"10 010", 170, 44},
        {"11 011", 140, 53},
        {"12 012", 170, 99},
        {"13 013", 180, 74},
        {"14 014", 173, 99},
        {"15 015", 121, 32},
        {"16 016", 111, 99},
        {"17 017", 170, 34},
        {"18 018", 170, 99},
        {"19 019", 170, 72},
        {"20 020", 170, 36}
    };

    int nx = sizeof(x) / sizeof(x[0]);  // 人数
    int adist[AMAX];                    // 年齢の分布

    
    for (int i = 0; i < nx; i++)
        printf("%s,%d,%d\n", x[i].name, x[i].height, x[i].age);

    printf("%5.1f\n", ave_height(x, nx));

    dist_vision(x, nx, adist); // ★修正：年齢分布を求める関数に修正済み

    
    for (int i = 0; i < AMAX; i++)
        printf("%d-：%2d\n", i, adist[i]);  // ★修正：表示も10歳刻みに
}
