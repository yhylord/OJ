#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 111, MAXM = 66666, INF = 1000000000;

int tot, s, t, d[MAXN], q[MAXN], g[MAXN], h[MAXN], p[MAXM], c[MAXM], nxt[MAXM], id[MAXM], ans[MAXM];

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

inline int dinic() {
    int ret = 0;
    while (bfs()) {
        memcpy(g, h, sizeof h);
        ret += dfs(s, INF);
    }
    return ret;
}

int main() {
    int n, m, sum = 0;
    scanf("%d%d", &n, &m);
    int rs = 0, rt = n + 1;
    s = rt + 1, t = s + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; ++i) {
        int x, y, z, c;
        scanf("%d%d%d%d", &x, &y, &z, &c);
        if (c) {
            sum += ans[i] = z;
            addedge(x, t, z);
            addedge(t, x, 0);
            addedge(s, y, z);
            addedge(y, s, 0);
        }
        else {
            addedge(x, y, z);
            id[tot] = i;
            addedge(y, x, 0);
        }
    }
    addedge(rs, 1, INF);
    addedge(1, rs, 0);
    addedge(n, rt, INF);
    addedge(rt, n, 0);
    addedge(rt, rs, INF);
    addedge(rs, rt, 0);
    if (dinic() != sum)
        puts("Impossible");
    else {
        s = rt, t = rs, sum = c[tot - 1];
        c[tot - 1] = c[tot - 2] = 0;
        printf("%d\n", sum - dinic());
        for (int i = 1; i <= n; ++i)
            for (int k = h[i]; ~k; k = nxt[k])
                if (id[k])
                    ans[id[k]] = c[k];
        for (int i = 1; i < m; ++i)
            printf("%d ", ans[i]);
        printf("%d\n", ans[m]);
    }
    return 0;
}
