#include <cstdio>
#include <cstring>

const int MAXM = 122, MOD = 45989;

int x[MAXM], y[MAXM], u[MAXM], v[MAXM][MAXM], w[MAXM][MAXM];

int main() {
    int n, m, t, a, b, ans = 0;
    scanf("%d%d%d%d%d", &n, &m, &t, &a, &b);
    for (int i = 0; i < m; ++i) {
        int j = i << 1;
        scanf("%d%d", &x[j], &y[j]);
        x[j ^ 1] = y[j], y[j ^ 1] = x[j];
    }
    m <<= 1;
    for (int i = 0; i < m; ++i) {
        if (x[i] == a)
            u[i] = 1;
        for (int j = 0; j < m; ++j)
            if ((i ^ 1) != j && y[i] == x[j])
                v[i][j] = 1;
    }
    for (--t; t; t >>= 1) {
        if (t & 1) {
            memset(w[0], 0, sizeof w[0]);
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < m; ++j)
                    (w[0][i] += u[j] * v[j][i]) %= MOD;
            memcpy(u, w[0], sizeof w[0]);
        }
        memset(w, 0, sizeof w);
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < m; ++j)
                for (int k = 0; k < m; ++k)
                    (w[i][j] += v[i][k] * v[k][j]) %= MOD;
        memcpy(v, w, sizeof w);
    }
    for (int i = 0; i < m; ++i)
        if (y[i] == b)
            ans += u[i];
    printf("%d\n", ans % MOD);
    return 0;
}
