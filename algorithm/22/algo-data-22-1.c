#include <stdio.h>

int main(void)
{
    int n;
    int i;
    int w;
    int v_i;
    int w_i;
    int dp[51];

    if (scanf("%d", &n) != 1) {
        return 0;
    }

    for (w = 0; w <= 50; w++) {
        dp[w] = 0;
    }

    for (i = 0; i < n; i++) {
        if (scanf("%d %d", &v_i, &w_i) != 2) {
            return 0;
        }

        for (w = 50; w >= w_i; w--) {
            int cand = dp[w - w_i] + v_i;
            if (cand > dp[w]) {
                dp[w] = cand;
            }
        }
    }

    printf("%d\n", dp[50]);

    return 0;
}
