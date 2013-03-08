#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 22222, MAXM = 444444;

bool b[MAXM];
int s, t, tot, d[MAXN], q[MAXN], g[MAXN], h[MAXN], p[MAXM], nxt[MAXM], c[MAXM], w[MAXM];

inline void addedge(int x, int y, int z) {
    p[tot] = y;
    w[tot] = z;
    c[tot] = 1;
    nxt[tot] = h[x];
    h[x] = tot++;
}

inline bool bfs() {
    memset(d, -1, sizeof d);
    int r = d[q[0] = s] = 0;
    for (int l = 0; l <= r; ++l)
        for (int k = h[q[l]]; ~k; k = nxt[k])
            if (b[k] && c[k] && !~d[p[k]])
                d[q[++r] = p[k]] = d[q[l]] + 1;
    return ~d[t];
}

int dfs(int x, int ext) {
    if (x == t)
        return ext;
    int flow;
    for (int &k = g[x]; ~k; k = nxt[k])
        if (b[k] && c[k] && d[p[k]] == d[x] + 1 && (flow = dfs(p[k], min(ext, c[k])))) {
            c[k] -= flow;
            c[k ^ 1] += flow;
            return flow;
        }
    return 0;
}

int main() {
    int n, m, l;
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addedge(x, y, z);
        addedge(y, x, z);
    }
    scanf("%d%d%d", &s, &t, &l);
    int ans = 0, flow;
    for (int i = 1; i <= n; ++i)
        for (int k = h[i]; ~k; k = nxt[k])
            b[k] = w[k] < l;
    while (bfs()) {
        memcpy(g, h, sizeof h);
        while (flow = dfs(s, MAXM))
            ans += flow;
    }
    for (int i = 1; i <= n; ++i)
        for (int k = h[i]; ~k; k = nxt[k])
            b[k] = w[k] > l;
    while (bfs()) {
        memcpy(g, h, sizeof h);
        while (flow = dfs(s, MAXM))
            ans += flow;
    }
    printf("%d\n", ans);
    return 0;
}
