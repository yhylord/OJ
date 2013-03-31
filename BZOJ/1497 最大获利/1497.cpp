#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 55555, MAXM = 444444, INF = 1000000000;

int tot, s, t, d[MAXN], q[MAXN], g[MAXN], h[MAXN], p[MAXM], c[MAXM], nxt[MAXM];

inline void addedge(int x, int y, int z) {
    p[tot] = y;
    c[tot] = z;
    nxt[tot] = h[x];
    h[x] = tot++;
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
    int n, m, ans = 0;
    scanf("%d%d", &n, &m);
    t = n + m + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        addedge(i, t, x);
        addedge(t, i, 0);
    }
    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        ans += z;
        addedge(s, n + i, z);
        addedge(n + i, s, 0);
        addedge(n + i, x, INF);
        addedge(x, n + i, 0);
        addedge(n + i, y, INF);
        addedge(y, n + i, 0);
    }
    while (bfs()) {
        memcpy(g, h, sizeof g);
        ans -= dfs(s, INF);
    }
    printf("%d\n", ans);
    return 0;
}
