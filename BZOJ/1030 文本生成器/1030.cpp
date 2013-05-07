#include <cstdio>

const int MAXN = 6666, MAXM = 111, MOD = 10007;

bool g[MAXN];
int nxt[MAXN][26], p[MAXN], q[MAXN], f[2][MAXM][MAXN];

int main() {
    int n, m, tot = 0, r = -1, ans = 0;
    scanf("%d%d%*c", &n, &m);
    for (int i = 0; i < n; ++i) {
        int x = 0;
        for (char c; (c = getchar()) != '\n'; x = nxt[x][c - 'A'])
            if (!nxt[x][c - 'A'])
                nxt[x][c - 'A'] = ++tot;
        g[x] = true;
    }
    for (int k = 0; k < 26; ++k)
        if (nxt[0][k])
            q[++r] = nxt[0][k];
    for (int l = 0; l <= r; ++l)
        for (int k = 0; k < 26; ++k) {
            int x = p[q[l]];
            for (; x && !nxt[x][k]; x = p[x]);
            if (nxt[q[l]][k]) {
                p[q[++r] = nxt[q[l]][k]] = nxt[x][k];
                g[q[r]] |= g[p[q[r]]];
            }
            else
                nxt[q[l]][k] = nxt[x][k];
        }
    f[0][0][0] = 1;
    for (int t = 0; t < 2; ++t)
        for (int i = 0; i < m; ++i)
            for (int j = 0; j <= tot; ++j)
                if (f[t][i][j])
                    for (int k = 0; k < 26; ++k)
                        (f[t | g[nxt[j][k]]][i + 1][nxt[j][k]] += f[t][i][j]) %= MOD;
    for (int i = 0; i <= tot; ++i)
        (ans += f[1][m][i]) %= MOD;
    printf("%d\n", ans);
    return 0;
}
