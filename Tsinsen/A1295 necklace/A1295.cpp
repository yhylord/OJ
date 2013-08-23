#include <cstdio>

const int MAXN = 1111, MAXM = 11;

double p[MAXN][MAXM], f[MAXN][MAXN][MAXM], g[MAXN][MAXN][MAXM], h[MAXN][MAXN][MAXM], u[MAXM][MAXN][MAXN];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int k = 1; k <= m; ++k)
            scanf("%lf", &p[i][k]);
    for (int k = 1; k <= m; ++k)
        for (int i = 1; i <= n; ++i) {
            u[k][i][i] = p[i][k];
            for (int j = i + 1; j <= n; ++j)
                u[k][i][j] = u[k][i][j - 1] * p[j][k];
        }
    f[0][1][0] = 1;
    for (int j = 0; j <= n; ++j)
        for (int l = 1; l <= m; ++l)
            h[0][j][l] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            if (j <= i)
                for (int k = 1; k <= m; ++k) {
                    f[i][j][k] += h[i - j][j][k] * u[k][i - j + 1][i];
                    if (j > 1)
                        f[i][j][k] += (g[i - 1][j][k] - g[i - j][j][k] * u[k][i - j + 1][i - 1]) * p[i][k];
                    g[i][j][0] += f[i][j][k];
                }
            for (int k = 1; k <= m; ++k) {
                g[i][j][k] = g[i - 1][j][k] * p[i][k] + g[i][j][0] - f[i][j][k];
                h[i][j][k] = h[i][j - 1][k] + g[i][j][0] - f[i][j][k];
            }
        }
    double ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int k = 1; k <= m; ++k)
            ans += f[n][i][k] * i;
    printf("%.6lf\n", ans);
    return 0;
}
