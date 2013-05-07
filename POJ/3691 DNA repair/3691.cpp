#include <cstdio>
#include <cstring>

const int MAXN = 1111;

bool g[MAXN];
char s[MAXN];
int id[128], nxt[MAXN][4], p[MAXN], q[MAXN], f[MAXN][MAXN];

inline void checkmin(int &x, int y) {
    if (y < x)
        x = y;
}

int main() {
    id['A'] = 0, id['G'] = 1, id['C'] = 2, id['T'] = 3;
    for (int n, cnt = 1; scanf("%d%*c", &n) && n; ++cnt) {
        int tot = 0, r = -1;
        memset(g, false, sizeof g);
        memset(nxt, 0, sizeof nxt);
        for (int i = 0; i < n; ++i) {
            int x = 0;
            for (char c; (c = getchar()) != '\n'; x = nxt[x][id[c]])
                if (!nxt[x][id[c]])
                    nxt[x][id[c]] = ++tot;
            g[x] = true;
        }
        for (int k = 0; k < 4; ++k)
            if (nxt[0][k])
                p[q[++r] = nxt[0][k]] = 0;
        for (int l = 0; l <= r; ++l)
            for (int k = 0; k < 4; ++k) {
                int x = p[q[l]];
                for (; x && !nxt[x][k]; x = p[x]);
                if (nxt[q[l]][k]) {
                    p[q[++r] = nxt[q[l]][k]] = nxt[x][k];
                    g[q[r]] |= g[p[q[r]]];
                }
                else
                    nxt[q[l]][k] = nxt[x][k];
            }
        int m = strlen(gets(s)), ans = MAXN;
        for (int i = 0; i <= m; ++i)
            for (int j = 0; j <= tot; ++j)
                f[i][j] = MAXN;
        for (int i = f[0][0] = 0; i < m; ++i)
            for (int j = 0; j <= tot; ++j)
                if (f[i][j] != MAXN)
                    for (int k = 0; k < 4; ++k)
                        if (!g[nxt[j][k]])
                            checkmin(f[i + 1][nxt[j][k]], f[i][j] + (id[s[i]] != k));
        for (int i = 0; i <= tot; ++i)
            checkmin(ans, f[m][i]);
        printf("Case %d: %d\n", cnt, ans == MAXN ? -1 : ans);
    }
    return 0;
}
