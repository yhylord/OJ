#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 5555, MAXM = 155555, INF = 1000000000;

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
    int flow;
    for (int &k = g[x]; ~k; k = nxt[k])
        if (c[k] && d[p[k]] == d[x] + 1 && (flow = dfs(p[k], min(c[k], ext)))) {
            c[k] -= flow;
            c[k ^ 1] += flow;
            return flow;
        }
    return 0;
}

int main() {
    int n, m, cnt = 0;
    long long ans = 0;
    scanf("%d%d", &n, &m);
    t = n + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        if (x >= 0) {
            ans += x;
            addedge(s, i, x);
            addedge(i, s, 0);
        }
        else {
            addedge(i, t, -x);
            addedge(t, i, 0);
        }
    }
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y, INF);
        addedge(y, x, 0);
    }
    while (bfs()) {
        int flow;
        memcpy(g, h, sizeof h);
        while (flow = dfs(s, INF))
            ans -= flow;
    }
    for (int i = 1; i <= n; ++i)
        cnt += bool(~d[i]);
    printf("%d %I64d\n", cnt, ans);
    return 0;
}
