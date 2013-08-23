#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long LL;

const int MAXN = 444, MAXM = 22222;
const LL INF = 1000000000000000LL;

int n, m;
LL a[MAXN], d1[MAXN], d2[MAXN];

struct graph {
    bool v[MAXN];
    int tot, s, t, q[MAXN], g[MAXN], h[MAXN], p[MAXM], c[MAXM], nxt[MAXM];
    LL d[MAXN];

    inline void clear() {
        tot = 0, s = 1, t = n, memset(h, -1, sizeof h);
    }

    inline void addedge(int x, int y, int z) {
        p[tot] = y, c[tot] = z, nxt[tot] = h[x], h[x] = tot++;
    }

    inline void dijkstra(int x) {
        for (int i = 0; i <= n; ++i)
            d[i] = INF, v[i] = false;
        d[x] = 0;
        for (int i = 1; i < n; ++i) {
            int u = 0;
            for (int j = 1; j <= n; ++j)
                if (!v[j] && d[j] < d[u])
                    u = j;
            v[u] = true;
            for (int k = h[u]; ~k; k = nxt[k])
                if (!v[p[k]] && d[u] + c[k] < d[p[k]])
                    d[p[k]] = d[u] + c[k];
        }
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

    LL dfs(int x, LL ext) {
        if (x == t)
            return ext;
        LL flow, ret = 0;
        for (int &k = g[x]; ~k; k = nxt[k])
            if (c[k] && d[p[k]] == d[x] + 1 && (flow = dfs(p[k], min(LL(c[k]), ext)))) {
                ret += flow, c[k] -= flow, c[k ^ 1] += flow;
                if (!(ext -= flow))
                    return ret;
            }
        return ret;
    }

    inline void dinic() {
        LL ans = 0;
        while (bfs()) {
            memcpy(g, h, sizeof h);
            ans += dfs(s, INF);
        }
        memset(v, false, sizeof v);
        int r = 0;
        v[q[0] = t] = true;
        for (int l = 0; l <= r; ++l)
            for (int k = h[q[l]]; ~k; k = nxt[k])
                if (c[k ^ 1] && !v[p[k]])
                    v[q[++r] = p[k]] = true;
        bool f = true;
        for (int i = 1; i <= n; ++i)
            if (~d[i])
                for (int k = h[i]; ~k; k = nxt[k])
                    if (!(k & 1) && !~d[p[k]])
                        if (!v[p[k]] || a[i] == a[p[k]])
                            f = false;
        printf("%s %lld\n", f ? "Yes" : "No", ans);
    }
} g1, g2;

inline void work() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i)
        scanf("%lld", &a[i]);
    a[n] = INF;
    g1.clear();
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        g1.addedge(x, y, z);
        g1.addedge(y, x, z);
    }
    g1.dijkstra(1);
    memcpy(d1, g1.d, sizeof g1.d);
    g1.dijkstra(n);
    memcpy(d2, g1.d, sizeof g1.d);
    g2.clear();
    for (int i = 1; i <= n; ++i)
        for (int k = g1.h[i]; ~k; k = g1.nxt[k])
            if (d1[i] + g1.c[k] + d2[g1.p[k]] == d1[n]) {
                g2.addedge(i, g1.p[k], min(a[i], a[g1.p[k]]));
                g2.addedge(g1.p[k], i, 0);
            }
    g2.dinic();
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--)
        work();
    return 0;
}
