#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 222, MAXM = 222222, INF = 1000000000;

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

int main() {
    int n, m, sum = 0, flow = 0;
    scanf("%d%d", &n, &m);
    t = n + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; ++i) {
        int x, y, a, b;
        scanf("%d%d%d%d", &x, &y, &a, &b);
        sum += ans[i] = a;
        addedge(x, y, b - a);
        id[tot] = i;
        addedge(y, x, 0);
        addedge(x, t, a);
        addedge(t, x, 0);
        addedge(s, y, a);
        addedge(y, s, 0);
    }
    while (bfs()) {
        memcpy(g, h, sizeof h);
        flow += dfs(s, INF);
    }
    if (flow != sum)
        puts("NO");
    else {
        puts("YES");
        for (int i = 1; i <= n; ++i)
            for (int k = h[i]; ~k; k = nxt[k])
                if (id[k])
                    ans[id[k]] += c[k];
        for (int i = 1; i <= m; ++i)
            printf("%d\n", ans[i]);
    }
    return 0;
}
