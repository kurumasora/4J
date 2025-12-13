#include <stdio.h>

#define MAX_NODES 100
#define INF_LL 0x3fffffffffffffffLL  /* 十分大きい値 */

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    if (n < 1 || n > MAX_NODES) {
        return 0;
    }

    long long w[MAX_NODES][MAX_NODES];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long x;
            if (scanf("%lld", &x) != 1) {
                return 0;
            }
            if (i == j) {
                /* 対角は 0 に正規化する．*/
                w[i][j] = 0;
            } else {
                /* 0 以下は辺なし扱い．正の値は重み．*/
                w[i][j] = (x <= 0) ? INF_LL : x;
            }
        }
    }

    int S;
    if (scanf("%d", &S) != 1) {
        return 0;
    }
    if (S < 0 || S >= n) {
        return 0;
    }

    long long dist[MAX_NODES];
    int used[MAX_NODES];
    for (int i = 0; i < n; i++) {
        dist[i] = INF_LL;
        used[i] = 0;
    }
    dist[S] = 0;

    /* Dijkstra（隣接行列版） */
    for (int iter = 0; iter < n; iter++) {
        int u = -1;
        long long best = INF_LL;
        for (int i = 0; i < n; i++) {
            if (!used[i] && dist[i] < best) {
                best = dist[i];
                u = i;
            }
        }
        if (u == -1) {
            break; /* 未到達のみが残った場合は終了．*/
        }
        used[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!used[v] && w[u][v] < INF_LL) {
                long long cand = dist[u] + w[u][v];
                if (cand < dist[v]) {
                    dist[v] = cand;
                }
            }
        }
    }

    /* 出力：各行「頂点番号 半角スペース 距離」．到達不能は -1 を出力．*/
    for (int i = 0; i < n; i++) {
        if (dist[i] >= INF_LL / 2) {
            printf("%d -1\n", i);
        } else {
            printf("%d %lld\n", i, dist[i]);
        }
    }
    return 0;
}
