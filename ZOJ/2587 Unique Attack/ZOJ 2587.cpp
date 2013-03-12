#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 888, MAXM = 22222, INF = 1000000000;

bool v[MAXN];
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
    int n, m;
    while (scanf("%d%d%d%d", &n, &m, &s, &t) && n) {
        tot = 0;
        memset(h, -1, sizeof h);
        while (m--) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            addedge(x, y, z);
            addedge(y, x, z);
        }
        while (bfs()) {
            memcpy(g, h, sizeof h);
            while (dfs(s, INF));
        }
        memset(v, false, sizeof v);
        int cnt = 0;
        for (int i = 1; i <= n; ++i)
            if (!~d[i])
                cnt += v[i] = true;
        for (int i = 1; i <= n; ++i)
            for (int k = h[i]; ~k; k = nxt[k])
                if (k & 1)
                    swap(c[k], c[k ^ 1]);
        swap(s, t);
        bfs();
        for (int i = 1; i <= n; ++i)
            if (!~d[i])
                cnt += v[i] = true;
        puts(cnt == n ? "UNIQUE" : "AMBIGUOUS");
    }
    return 0;
}
