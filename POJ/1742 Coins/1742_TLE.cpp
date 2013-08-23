#include <cstdio>

const int MAXN = 111, MAXM = 111111;

int a[MAXN], c[MAXN], f[MAXM][2], s[MAXM];

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) && n) {
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &c[i]);
        for (int i = 0; i <= m; ++i)
            f[i][0] = f[i][1] = -1;
        f[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            int p = i & 1, q = p ^ 1, t = c[i] * a[i];
            for (int j = 0; j < a[i]; ++j) {
                int l = 0, r = -1;
                for (int k = j; k <= m; k += a[i]) {
                    for (; l <= r && k - s[l] > t; ++l);
                    if (f[k][q] == i - 1)
                        s[++r] = k;
                    if (l <= r)
                        f[k][p] = i;
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= m; ++i)
            ans += f[i][n & 1] == n;
        printf("%d\n", ans);
    }
    return 0;
}
