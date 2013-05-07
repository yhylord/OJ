#include <cstdio>
#include <cstring>

const int MAXL = 66, MOD = 10007;

bool e[MAXL];
unsigned tot, nxt[MAXL][26], p[MAXL], q[MAXL], g[MAXL][MAXL], u[MAXL][MAXL], ans[MAXL];

int main() {
    int n, m;
    while (scanf("%d%d%*c", &n, &m) != EOF) {
        memset(nxt, tot = 0, sizeof nxt);
        memset(e, false, sizeof e);
        while (n--) {
            int x = 0;
            for (char c; (c = getchar()) != '\n'; x = nxt[x][c - 'A'])
                if (!nxt[x][c - 'A'])
                    nxt[x][c - 'A'] = ++tot;
            e[x] = true;
        }
        int r = -1;
        for (int k = 0; k < 26; ++k)
            if (nxt[0][k])
                p[q[++r] = nxt[0][k]] = 0;
        for (int l = 0; l <= r; ++l)
            for (int k = 0; k < 26; ++k) {
                int x = p[q[l]];
                for (; x && !nxt[x][k]; x = p[x]);
                if (nxt[q[l]][k]) {
                    p[q[++r] = nxt[q[l]][k]] = nxt[x][k];
                    e[q[r]] |= e[p[q[r]]];
                }
                else
                    nxt[q[l]][k] = nxt[x][k];
            }
        memset(g, 0, sizeof g);
        g[++tot][tot] = 26;
        for (int i = 0; i < tot; ++i)
            for (int k = 0; k < 26; ++k)
                ++g[i][e[nxt[i][k]] ? tot : nxt[i][k]];
        memset(ans, 0, sizeof ans);
        ans[0] = 1;
        for (; m; m >>= 1) {
            if (m & 1) {
                for (int i = 0; i <= tot; ++i) {
                    u[0][i] = 0;
                    for (int j = 0; j <= tot; ++j)
                        u[0][i] += ans[j] * g[j][i];
                    u[0][i] %= MOD;
                }
                memcpy(ans, u[0], sizeof u[0]);
            }
            for (int i = 0; i <= tot; ++i)
                for (int j = 0; j <= tot; ++j) {
                    u[i][j] = 0;
                    for (int k = 0; k <= tot; ++k)
                        u[i][j] += g[i][k] * g[k][j];
                    u[i][j] %= MOD;
                }
            memcpy(g, u, sizeof g);
        }
        printf("%d\n", ans[tot] % MOD);
    }
    return 0;
}
