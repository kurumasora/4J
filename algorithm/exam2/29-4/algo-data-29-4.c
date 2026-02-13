#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100 

int adj[MAX_NODES][MAX_NODES]; // 隣接行列 [cite: 6]
int visited[MAX_NODES];        // 訪問フラグ
int n;                         // ノード数

// 深さ優先探索 (DFS) による探索 
void dfs(int u) {
    visited[u] = 1;
    for (int v = 0; v < n; v++) {
        // 接続があり、かつ未訪問のノードを探索
        if (adj[u][v] == 1 && !visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    int start_node;
    
    // 1行目: ノード数の入力 [cite: 8, 9]
    if (scanf("%d", &n) != 1) return 1;
    
    // 2行目: 開始ノードの入力 [cite: 8, 10]
    if (scanf("%d", &start_node) != 1) return 1;
    
    // 3行目以降: 隣接行列の読み込み 
    for (int i = 0; i < n; i++) {
        int row_idx;
        scanf("%d", &row_idx); // 行の先頭のノード番号を読み飛ばす/取得
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    // 全訪問フラグを初期化
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    // 探索開始 (ノード番号は1から始まる想定のため -1 で補正)
    dfs(start_node - 1);

    // 全てのノードが訪問されたか確認 
    int connected = 1;
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            connected = 0;
            break;
        }
    }

    // 結果の出力 [cite: 18, 19]
    if (connected) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}