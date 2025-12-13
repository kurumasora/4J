#include <stdio.h>

#define MAX_NODES 100

int graph[MAX_NODES][MAX_NODES]; // 隣接行列
int visited[MAX_NODES]; // 訪問済みノードの管理

// 深さ優先探索
void dfs(int node, int n) {
    visited[node] = 1;
    printf("%d\n", node + 1); // 1-based indexing で出力

    // 隣接する未訪問のノードに対して再帰的にDFS
    for (int i = 0; i < n; i++) {
        if (graph[node][i] == 1 && !visited[i]) {
            dfs(i, n);
        }
    }
}

int main() {
    int n, s;

    // 入力の受け取り
    scanf("%d", &n);
    
    // 隣接行列の入力
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // 始点の入力
    scanf("%d", &s);
    
    // 訪問の初期化
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    // 深さ優先探索を実行
    dfs(s - 1, n); // 0-based indexing のため、s-1

    return 0;
}
