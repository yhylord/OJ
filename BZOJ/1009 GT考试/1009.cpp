#include <cstdio>
#include <cstring>

const int MAXN = 22;

char s[MAXN];
int p[MAXN], nxt[MAXN][10], u[MAXN], v[MAXN][MAXN], w[MAXN][MAXN];

int main() {
    int n, m, MOD, ans = 0;
    scanf("%d%d%d%s", &n, &m, &MOD, s + 1);
    for (int i = 2, j = 0; i <= m; ++i) {
        for (; j && s[j + 1] != s[i]; j = p[j]);
        p[i] = j += s[j + 1] == s[i];
    }
    for (int i = 0; i <= m; ++i)
        for (int k = 0; k < 10; ++k) {
            if (s[i + 1] - 48 == k)
                nxt[i][k] = i + 1;
            else {
                int x = p[i];
                for (; x && !nxt[x][k]; x = p[x]);
                nxt[i][k] = nxt[x][k];
            }
            if (nxt[i][k] != m)
                ++v[i][nxt[i][k]];
        }
    u[0] = 1;
    for (; n; n >>= 1) {
        if (n & 1) {
            for (int i = 0; i <= m; ++i) {
                w[0][i] = 0;
                for (int j = 0; j <= m; ++j)
                    w[0][i] += u[j] * v[j][i];
                w[0][i] %= MOD;
            }
            memcpy(u, w[0], sizeof w[0]);
        }
        for (int i = 0; i <= m; ++i)
            for (int j = 0; j <= m; ++j) {
                w[i][j] = 0;
                for (int k = 0; k <= m; ++k)
                    w[i][j] += v[i][k] * v[k][j];
                w[i][j] %= MOD;
            }
        memcpy(v, w, sizeof w);
    }
    for (int i = 0; i <= m; ++i)
        ans += u[i];
    printf("%d\n", ans % MOD);
    return 0;
}
