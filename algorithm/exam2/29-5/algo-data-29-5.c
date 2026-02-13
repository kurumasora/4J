#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100
#define INF 1000000 // 十分に大きな値

int n;                     // ノード数
int adj[MAX_NODES][MAX_NODES]; // 隣接行列（重み付き） [cite: 39]
int dist[MAX_NODES];       // 始点からの最短距離
bool visited[MAX_NODES];   // 訪問済みフラグ

void dijkstra(int start) {
    // 距離の初期化
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = false;
    }
    dist[start] = 0;

    for (int count = 0; count < n; count++) {
        // 未訪問の中で最短距離のノードを探す
        int u = -1;
        int min_dist = INF;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                u = i;
            }
        }

        if (u == -1) break; // 到達可能なノードがなくなった場合

        visited[u] = true;

        // 隣接ノードの距離を更新
        for (int v = 0; v < n; v++) {
            // エッジが存在し(adj[u][v] > 0)、未訪問の場合
            if (adj[u][v] > 0 && !visited[v]) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
    }
}

int main() {
    int start_node;

    // 1行目: ノード数 [cite: 41, 42]
    if (scanf("%d", &n) != 1) return 1;
    // 2行目: 始点 [cite: 41, 43]
    if (scanf("%d", &start_node) != 1) return 1;

    // 3行目以降: 隣接行列の読み込み [cite: 41, 44-47]
    for (int i = 0; i < n; i++) {
        int dummy;
        scanf("%d", &dummy); // 行頭のノード番号を読み飛ばす
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    // ダイクストラ法の実行 (1-indexedを0-indexedに調整)
    dijkstra(start_node - 1);

    // 各頂点への最短距離を出力
    for (int i = 0; i < n; i++) {
        printf("Node %d: %d\n", i + 1, dist[i]);
    }

    return 0;
}