#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 222, MAXM = 11111, INF = 1000000000;

int s, t, tot = -1, q[MAXN], d[MAXN], g[MAXN], h[MAXN], p[MAXM], c[MAXM], nxt[MAXM];

inline void addedge(int x, int y, int z) {
    p[++tot] = y;
    c[tot] = z;
    nxt[tot] = h[x];
    h[x] = tot;
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
    int flow;
    for (int &k = g[x]; ~k; k = nxt[k])
        if (c[k] && d[p[k]] == d[x] + 1 && (flow = dfs(p[k], min(ext, c[k])))) {
            c[k] -= flow;
            c[k ^ 1] += flow;
            return flow;
        }
    return 0;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    t = 2 * n + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        addedge(n + i, t, x);
        addedge(t, n + i, 0);
    }
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        addedge(s, i, x);
        addedge(i, s, 0);
    }
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y + n, INF);
        addedge(y + n, x, 0);
    }
    int ans = 0;
    while (bfs()) {
        int flow;
        memcpy(g, h, sizeof h);
        while (flow = dfs(s, INF))
            ans += flow;
    }
    printf("%d\n", ans);
    int cnt = 0;
    for (int i = s; i <= t; ++i)
        if (~d[i])
            for (int k = h[i]; ~k; k = nxt[k])
                if (!~d[p[k]] && (i == s || p[k] == t))
                    ++cnt;
    printf("%d\n", cnt);
    for (int i = s; i <= t; ++i)
        if (~d[i])
            for (int k = h[i]; ~k; k = nxt[k])
                if (!~d[p[k]])
                    if (i == s)
                        printf("%d -\n", p[k]);
                    else if (p[k] == t)
                        printf("%d +\n", i - n);
    return 0;
}
