#include <cstdio>

const int MAXN = 333333, MAXQ = 1444444;

int g[MAXN][4], c[MAXN], q[MAXQ];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    while (m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a][++g[a][0]] = b;
        g[b][++g[b][0]] = a;
    }
    for (int i = 1; i <= n; ++i)
        q[i] = i;
    int l = 1, r = n;
    for (; l <= r; ++l) {
        int u = q[l], t = 0;
        for (int i = 1; i <= g[u][0]; ++i)
            if (c[g[u][i]] == c[u])
                ++t;
        if (t > 1) {
            c[u] ^= 1;
            for (int i = 1; i <= g[u][0]; ++i) {
                int v = g[u][i];
                t = 0;
                for (int j = 1; j <= g[v][0]; ++j)
                    if (c[g[v][j]] == c[v])
                        ++t;
                if (t > 1)
                    q[++r] = v;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        printf("%d", c[i]);
    putchar('\n');
    return 0;
}
