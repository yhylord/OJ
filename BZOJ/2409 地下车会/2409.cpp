#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 1111, MAXM = 2222222, INF = 1000000000;

int tot, s, t, lo[MAXN][MAXN], hi[MAXN][MAXN], d[MAXN], q[MAXN],
    g[MAXN], h[MAXN], p[MAXM], c[MAXM], nxt[MAXM];

inline void addedge(int x, int y, int z) {
    p[tot] = y;
    c[tot] = z;
    nxt[tot] = h[x];
    h[x] = tot++;
}

inline void add(int x, int y, int z) {
    addedge(x, y, z);
    addedge(y, x, 0);
}

inline void set(int x, int y, int l, int r) {
    add(s, y, l);
    add(x, t, l);
    add(x, y, r - l);
}

inline bool bfs() {
    memset(d, -1, sizeof d);
    int r = d[q[0] = s] = 0;
    for (int l = 0; l <= r; ++l)
        for (int k = h[q[l]]; ~k; k = nxt[k])
            if (c[k] && !~d[p[k]])
                d[q[++r] = p[k]] = d[q[l]] + 1;
    return ~d[t];
}

int dfs(int x, int ext) {
    if (x == t)
        return ext;
    int flow, ret = 0;
    for (int &k = g[x]; ~k; k = nxt[k])
        if (c[k] && d[p[k]] == d[x] + 1 && (flow = dfs(p[k], min(c[k], ext)))) {
            ret += flow;
            c[k] -= flow;
            c[k ^ 1] += flow;
            if (!(ext -= flow))
                return ret;
        }
    return ret;
}

int main() {
    int n, m, k, x, y, z;
    scanf("%d%d%d", &n, &m, &k);
    int rs = 0, rt = n + m + 1;
    s = rt + 1, t = rt + 2;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        while (x--) {
            scanf("%d", &y);
            ++hi[i][y];
        }
    }
    scanf("%d", &z);
    while (z--) {
        scanf("%d%d", &x, &y);
        ++lo[x][y];
    }
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &x);
        add(n + i, rt, x);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &x, &y);
        set(rs, i, y, x);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (lo[i][j])
                set(i, n + j, lo[i][j], hi[i][j]);
            else
                add(i, n + j, hi[i][j]);
    add(rt, rs, INF);
    while (bfs()) {
        memcpy(g, h, sizeof h);
        dfs(s, INF);
    }
    int ans = c[tot - 1];
    c[tot - 1] = c[tot - 2] = 0;
    s = rs, t = rt;
    while (bfs()) {
        memcpy(g, h, sizeof h);
        ans += dfs(s, INF);
    }
    printf("%d\n", min(ans, k));
    return 0;
}
