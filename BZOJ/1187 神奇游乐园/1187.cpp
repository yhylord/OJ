#include <cstdio>
#include <cstring>

const int MAXN = 111, MAXM = 7, INF = 1000000000;

int n, m, a[MAXN][MAXM], f[MAXN][MAXM][1 << (MAXM << 1)];

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

inline int get(int k, int i) {
    return (k >> (m - i << 1)) & 3;
}

inline int set(int k, int i, int v) {
    return k ^ ((v ? v : get(k, i)) << (m - i << 1));
}

inline int find(int k, int i, int d, int g) {
    for (i += d; get(k, i) != g; i += d);
    return i;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &a[i][j]);
    memset(f, -63, sizeof f);
    f[0][m][0] = 0;
    int s = 1 << (m + 1 << 1), ans = -INF;
    for (int i = 1; i <= n; ++i) {
        for (int k = 0; k < s; ++k)
            if (f[i - 1][m][k] > -INF)
                checkmax(f[i][0][k >> 2], f[i - 1][m][k]);
        for (int j = 1; j <= m; ++j)
            for (int k = 0; k < s; ++k)
                if (f[i][j - 1][k] > -INF) {
                    int p = get(k, j - 1), q = get(k, j);
                    if (!p && !q) {
                        checkmax(f[i][j][k], f[i][j - 1][k]);
                        if (i < n && j < m)
                            checkmax(f[i][j][set(set(k, j - 1, 1), j, 2)], f[i][j - 1][k] + a[i][j]);
                    }
                    else if (!p || !q) {
                        if (!p && j < m || !q && i < n)
                            checkmax(f[i][j][k], f[i][j - 1][k] + a[i][j]);
                        if (!p && i < n || !q && j < m)
                            checkmax(f[i][j][set(set(k, j - 1, q), j, p)], f[i][j - 1][k] + a[i][j]);
                    }
                    else
                        if (p == 1 && q == 2) {
                            if ((k ^ set(0, j - 1, p) ^ set(0, j, q)) == 0)
                                checkmax(ans, f[i][j - 1][k] + a[i][j]);
                        }
                        else if (p == 2 && q == 1)
                            checkmax(f[i][j][set(set(k, j - 1, 0), j, 0)], f[i][j - 1][k] + a[i][j]);
                        else {
                            int d = p == 1 ? 1 : -1, g = 3 - p, t = find(k, j, d, g);
                            checkmax(f[i][j][set(set(set(set(k, j - 1, 0), j, 0), t, 0), t, p)], f[i][j - 1][k] + a[i][j]);
                        }
                }
    }
    printf("%d\n", ans);
    return 0;
}
