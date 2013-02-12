#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 33, MAXM = 555;

double g[MAXN][MAXN], c[MAXM][MAXM], ans[MAXM];
int d[MAXN];

int main() {
    int n, m, a, b;
    scanf("%d%d%d%d", &n, &m, &a, &b);
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        ++d[--x];
        ++d[--y];
        g[x][y] = g[y][x] = 1;
    }
    for (int i = 0; i < n; ++i)
        scanf("%lf", &g[i][i]);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j)
                g[i][j] *= (1 - g[i][i]) / d[i];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            for (int x = 0; x < n; ++x)
                for (int y = 0; y < n; ++y)
                    if (x != y)
                        c[i * n + j][x * n + y] = g[x][i] * g[y][j];
            --c[i * n + j][i * n + j];
        }
    c[--a * n + --b][m = n * n] = -1;
    for (int k = 0; k < m; ++k) {
        int x = -1;
        for (int i = k; i < m && !~x; ++i)
            if (c[i][k])
                x = i;
        for (int j = k; j <= m; ++j)
            swap(c[x][j], c[k][j]);
        for (int i = k + 1; i < m; ++i)
            if (c[i][k]) {
                double t = c[i][k] / c[k][k];
                for (int j = k; j <= m; ++j)
                    c[i][j] -= c[k][j] * t;
            }
    }
    for (int i = m - 1; i >= 0; --i) {
        ans[i] = c[i][m];
        for (int j = m - 1; j > i; --j)
            ans[i] -= ans[j] * c[i][j];
        ans[i] /= c[i][i];
    }
    for (int i = 0; i < n - 1; ++i)
        printf("%.8lf ", ans[i * n + i]);
    printf("%.8lf\n", ans[(n - 1) * n + n - 1]);
    return 0;
}
