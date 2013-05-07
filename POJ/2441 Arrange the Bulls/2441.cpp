#include <cstdio>

const int MAXN = 21;

int a[MAXN][MAXN], f[1 << MAXN - 1];

int main() {
    int n, m, ans = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i][0]);
        for (int j = 1; j <= a[i][0]; ++j)
            scanf("%d", &a[i][j]);
    }
    f[0] = 1;
    for (int i = 1; i < 1 << m; ++i) {
        int c = 0;
        for (int j = 0; j < m; ++j)
            c += (i >> j) & 1;
        for (int j = 1; j <= a[c][0]; ++j)
            if ((i >> a[c][j] - 1) & 1)
                f[i] += f[i ^ (1 << a[c][j] - 1)];
        if (c == n)
            ans += f[i];
    }
    printf("%d\n", ans);
    return 0;
}
