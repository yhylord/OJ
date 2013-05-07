#include <cstdio>
#include <cstring>

const int MAXN = 155, MAXM = 11;

bool g[MAXN][MAXM], p[MAXN][MAXM], q[MAXN][MAXM];
int f[2][60000], m;

void dfs(int no, int dep, int s1, int s2, int c) {
    if (dep > m) {
        int u = no & 1;
        if (f[u ^ 1][s2] + c > f[u][s1])
            f[u][s1] = f[u ^ 1][s2] + c;
        return;
    }
    if (p[no][dep])
        dfs(no, dep + 3, s1 * 27 + 26, s2 * 27 + 13, c + 1);
    if (q[no][dep])
        dfs(no, dep + 2, s1 * 9 + 8, s2 * 9, c + 1);
    dfs(no, dep + 1, s1 * 3, s2 * 3 + 1, c);
    dfs(no, dep + 1, s1 * 3 + 1, s2 * 3 + 2, c);
    dfs(no, dep + 1, s1 * 3 + 2, s2 * 3 + 2, c);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, k;
        scanf("%d%d%d", &n, &m, &k);
        memset(g, true, sizeof g);
        memset(p, true, sizeof p);
        memset(q, true, sizeof q);
        for (int i = 1; i <= k; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            g[x][y] = false;
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                if (i < 2 || j + 2 > m)
                    p[i][j] = false;
                else
                    p[i][j] = g[i][j] & g[i][j + 1] & g[i][j + 2] & g[i - 1][j] & g[i - 1][j + 1] & g[i - 1][j + 2];
                if (i < 3 || j + 1 > m)
                    q[i][j] = false;
                else
                    q[i][j] = g[i][j] & g[i][j + 1] & g[i - 1][j] & g[i - 1][j + 1] & g[i - 2][j] & g[i - 2][j + 1];
            }
        memset(f[0], 0, sizeof f[0]);
        for (int i = 1; i <= n; ++i) {
            memset(f[i & 1], 0, sizeof f[i & 1]);
            dfs(i, 1, 0, 0, 0);
        }
        int r = 1;
        for (int i = 1; i <= m; ++i)
            r *= 3;
        printf("%d\n", f[n & 1][r - 1]);
    }
    return 0;
}
