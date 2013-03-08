#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 555, MAXM = 8888, MAXB = 31, INF = 1000000000;

int s, t, u, ans[MAXN], tot[MAXB], d[MAXN], q[MAXN], g[MAXN],
    h[MAXB][MAXN], p[MAXB][MAXM], c[MAXB][MAXM], nxt[MAXB][MAXM];

inline void addedge(int x, int y, int z) {
    p[u][tot[u]] = y;
    c[u][tot[u]] = z;
    nxt[u][tot[u]] = h[u][x];
    h[u][x] = tot[u]++;
}

inline bool bfs() {
    memset(d, -1, sizeof d);
    int r = d[q[0] = s] = 0;
    for (int l = 0; l <= r; ++l)
        for (int k = h[u][q[l]]; ~k; k = nxt[u][k])
            if (c[u][k] && !~d[p[u][k]])
                d[q[++r] = p[u][k]] = d[q[l]] + 1;
    return ~d[t];
}

int dfs(int x, int ext) {
    if (x == t)
        return ext;
    int flow;
    for (int &k = g[x]; ~k; k = nxt[u][k])
        if (c[u][k] && d[p[u][k]] == d[x] + 1 && (flow = dfs(p[u][k], min(c[u][k], ext)))) {
            c[u][k] -= flow;
            c[u][k ^ 1] += flow;
            return flow;
        }
    return 0;
}

int main() {
    int cs;
    scanf("%d", &cs);
    while (cs--) {
        int n, m;
        scanf("%d%d", &n, &m);
        memset(h, -1, sizeof h);
        memset(tot, 0, sizeof tot);
        t = n + 1;
        while (m--) {
            int x, y;
            scanf("%d%d", &x, &y);
            for (u = 0; u < MAXB; ++u) {
                addedge(x, y, 1);
                addedge(y, x, 1);
            }
        }
        scanf("%d", &m);
        while (m--) {
            int x, y;
            scanf("%d%d", &x, &y);
            for (u = 0; u < MAXB; ++u)
                if ((y >> u) & 1) {
                    addedge(s, x, INF);
                    addedge(x, s, 0);
                }
                else {
                    addedge(x, t, INF);
                    addedge(t, x, 0);
                }
        }
        memset(ans, 0, sizeof ans);
        for (u = 0; u < MAXB; ++u) {
            while (bfs()) {
                memcpy(g, h[u], sizeof h[u]);
                while (dfs(s, INF));
            }
            for (int i = 1; i <= n; ++i)
                if (~d[i])
                    ans[i] |= 1 << u;
        }
        for (int i = 1; i <= n; ++i)
            printf("%d\n", ans[i]);
    }
    return 0;
}
