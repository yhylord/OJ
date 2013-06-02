#include <cstdio>
#include <cstring>

const int MAXN = 777, MAXM = 11, INF = 1000000000;

int n, mx, go, bx, by, a[MAXN], b[MAXN], s[MAXN], c[MAXN],
    g[MAXN], e[MAXN][MAXM], f[(1 << MAXM) + 1];

inline void checkmin(int &x, int y) {
    if (y < x)
        x = y;
}

void dfs(int x, int y, int d) {
    s[++s[0]] = x;
    if (d > mx) {
        mx = d, go = x;
        memcpy(c, s, sizeof s);
    }
    for (int i = 0; i < g[x]; ++i)
        if (e[x][i] != y)
            dfs(e[x][i], x, d + 1);
    --s[0];
}

void build(int x, int y) {
    int cnt = 0, t[MAXM];
    for (int i = 0; i < g[x]; ++i)
        if (e[x][i] != y && !(x == bx && e[x][i] == by || x == by && e[x][i] == bx))
            t[cnt++] = e[x][i];
    g[x] = cnt;
    memcpy(e[x], t, sizeof t);
    for (int i = 0; i < g[x]; ++i)
        build(e[x][i], x);
}

int dp(int x, int y) {
    if (g[x] != g[y])
        return INF;
    int r[MAXM][MAXM];
    for (int i = 0; i < g[x]; ++i)
        for (int j = 0; j < g[y]; ++j)
            r[i][j] = dp(e[x][i], e[y][j]);
    for (int i = 0; i < 1 << g[x]; ++i)
        f[i] = INF;
    f[(1 << g[x]) - 1] = 0;
    for (int i = (1 << g[x]) - 1; i; --i)
        if (f[i] < INF) {
            int cnt = g[x];
            for (int j = 0; j < g[x]; ++j)
                if (i & (1 << j))
                    --cnt;
            for (int j = 0; j < g[x]; ++j)
                if (i & (1 << j))
                    checkmin(f[i ^ (1 << j)], f[i] + r[cnt][j]);
        }
    return f[0] + (a[x] != b[y]);
}

int main() {
    int n, root;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        e[x][g[x]++] = y;
        e[y][g[y]++] = x;
    }
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &b[i]);
    dfs(1, 0, 0);
    dfs(go, mx = 0, 0);
    if (c[0] & 1)
        root = c[1 + c[0] >> 1];
    else {
        root = n + 1;
        bx = e[root][g[root]++] = c[c[0] >> 1];
        by = e[root][g[root]++] = c[(c[0] >> 1) + 1];
    }
    build(root, 0);
    printf("%d\n", dp(root, root));
    return 0;
}
