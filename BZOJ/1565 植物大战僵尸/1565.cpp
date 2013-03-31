#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 666, MAXM = 777777, INF = 1000000000;

bool v[MAXN];
int tot, m, s, t, a[MAXN], d[MAXN], q[MAXN], g[MAXN], h[MAXN], p[MAXM], c[MAXM], nxt[MAXM];

inline int no(int x, int y) {
    return (x - 1) * m + y;
}

inline void addedge(int x, int y, int z) {
    d[p[tot] = y] += tot & 1;
    c[tot] = z;
    nxt[tot] = h[x];
    h[x] = tot++;
}

inline bool bfs() {
    memset(d, -1, sizeof d);
    int r = d[q[0] = s] = 0;
    for (int l = 0; l <= r; ++l)
        for (int k = h[q[l]]; ~k; k = nxt[k])
            if (c[k] && v[p[k]] && !~d[p[k]])
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
    int n;
    scanf("%d%d", &n, &m);
    t = n * m + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            int x, y, z;
            scanf("%d", &x);
            a[no(i, j)] = x;
            if (x >= 0) {
                addedge(s, no(i, j), x);
                addedge(no(i, j), s, 0);
            }
            else {
                addedge(no(i, j), t, -x);
                addedge(t, no(i, j), 0);
            }
            scanf("%d", &z);
            while (z--) {
                scanf("%d%d", &x, &y);
                addedge(no(x + 1, y + 1), no(i, j), INF);
                addedge(no(i, j), no(x + 1, y + 1), 0);
            }
            if (j < m) {
                addedge(no(i, j), no(i, j + 1), INF);
                addedge(no(i, j + 1), no(i, j), 0);
            }
        }
    int r = -1, ans = 0;
    for (int i = s; i <= t; ++i)
        if (!d[i])
            v[q[++r] = i] = true;
    for (int l = 0; l <= r; ++l)
        for (int k = h[q[l]]; ~k; k = nxt[k])
            if ((k & 1) && !v[p[k]] && --d[p[k]] == 0)
                v[q[++r] = p[k]] = true;
    for (int i = s; i <= t; ++i)
        if (v[i] && a[i] > 0)
            ans += a[i];
    while (bfs()) {
        memcpy(g, h, sizeof g);
        ans -= dfs(s, INF);
    }
    printf("%d\n", ans);
    return 0;
}
