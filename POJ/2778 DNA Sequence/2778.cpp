#include <cstdio>

typedef long long LL;

const int MAXL = 101, MOD = 100000;

bool e[MAXL];
char s[22];
int tot, p[MAXL], q[MAXL], nxt[MAXL][4], id[128];

struct mat {
    int a[MAXL][MAXL];

    inline mat operator * (const mat &x) {
        mat y;
        for (int i = 0; i <= tot; ++i)
            for (int j = 0; j <= tot; ++j) {
                y.a[i][j] = 0;
                for (int k = 0; k <= tot; ++k)
                    y.a[i][j] += LL(a[i][k]) * x.a[k][j] % MOD;
                y.a[i][j] %= MOD;
            }
        return y;
    }
} g, u;

int main() {
    id['A'] = 0, id['C'] = 1, id['T'] = 2, id['G'] = 3;
    int m, n, r = -1, ans = 0;
    for (scanf("%d%d", &m, &n); m--; ) {
        int x = 0;
        scanf("%s", s);
        for (int i = 0; s[i]; x = nxt[x][id[s[i++]]])
            if (!nxt[x][id[s[i]]])
                nxt[x][id[s[i]]] = ++tot;
        e[x] = true;
    }
    for (int k = 0; k < 4; ++k)
        if (nxt[0][k])
            q[++r] = nxt[0][k];
    for (int l = 0; l <= r; ++l)
        for (int k = 0; k < 4; ++k) {
            int x = p[q[l]];
            for (; x && !nxt[x][k]; x = p[x]);
            if (nxt[q[l]][k]) {
                p[q[++r] = nxt[q[l]][k]] = nxt[x][k];
                e[q[r]] |= e[p[q[r]]];
            }
            else
                nxt[q[l]][k] = nxt[x][k];
        }
    for (int i = 0; i <= tot; ++i)
        if (!e[i])
            for (int k = 0; k < 4; ++k)
                g.a[i][nxt[i][k]] += !e[nxt[i][k]];
    bool f = true;
    for (int i = 0; n >= 1U << i; ++i, g = g * g)
        if (n & (1 << i))
            if (f) {
                f = false;
                u = g;
            }
            else
                u = u * g;
    for (int i = 0; i <= tot; ++i)
        ans += u.a[0][i];
    printf("%d\n", ans % MOD);
    return 0;
}
