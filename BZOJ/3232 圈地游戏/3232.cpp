#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const double INF = 1e10;
const int MAXN = 3333, MAXM = 22222, MAXC = 55;

double c[MAXM];
int tot, s, t, n, m, d[MAXN], q[MAXN], g[MAXN], h[MAXN], p[MAXM], nxt[MAXM],
    id[MAXC][MAXC], a[MAXC][MAXC], b[MAXC][MAXC], e[MAXC][MAXC];

inline void addedge(int x, int y, double z) {
    p[tot] = y, c[tot] = z, nxt[tot] = h[x], h[x] = tot++;
}

inline void add(int x, int y, double z1, double z2) {
    addedge(x, y, z1), addedge(y, x, z2);
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

double dfs(int x, double ext) {
    if (x == t)
        return ext;
    double flow, ret = 0;
    for (int &k = g[x]; ~k; k = nxt[k])
        if (c[k] && d[p[k]] == d[x] + 1 && (flow = dfs(p[k], min(c[k], ext)))) {
            ret += flow, c[k] -= flow, c[k ^ 1] += flow;
            if (!(ext -= flow))
                return ret;
        }
    return ret;
}

inline double dinic(double mid) {
    double ret = tot = 0;
    memset(h, -1, sizeof h);
    for (int i = 0; i <= n + 1; ++i)
        for (int j = 0; j <= m + 1; ++j)
            if (!i || i == n + 1 || !j || j == m + 1)
                add(id[i][j], t, INF, 0);
            else
                add(s, id[i][j], e[i][j], 0), ret += e[i][j];
    for (int i = 0; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            add(id[i][j], id[i + 1][j], mid * a[i][j], mid * a[i][j]);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            add(id[i][j], id[i][j + 1], mid * b[i][j], mid * b[i][j]);
    while (bfs()) {
        memcpy(g, h, sizeof h);
        ret -= dfs(s, INF);
    }
    return ret;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &e[i][j]);
    for (int i = 0; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            scanf("%d", &b[i][j]);
    for (int i = 0; i <= n + 1; ++i)
        for (int j = 0; j <= m + 1; ++j)
            id[i][j] = s++;
    t = s + 1;
    double l = 0, r = n * m * 100;
    while (r - l > 1e-5) {
        double mid = (l + r) / 2;
        if (dinic(mid) < 1e-9)
            r = mid;
        else
            l = mid;
    }
    printf("%.3lf\n", l);
    return 0;
}
