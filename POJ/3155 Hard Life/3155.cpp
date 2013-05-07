#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const double EPS = 1e-6, INF = 1e10;
const int MAXN = 1111, MAXM = 6666;

double c[MAXM];
int tot, s, t, n, m, d[MAXN], q[MAXN], g[MAXN], h[MAXN], p[MAXM], nxt[MAXM];
pair<int, int> e[MAXN];

inline void addedge(int x, int y, double z) {
    p[tot] = y;
    c[tot] = z;
    nxt[tot] = h[x];
    h[x] = tot++;
}

inline void add(int x, int y, double z) {
    addedge(x, y, z);
    addedge(y, x, 0);
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

inline double dfs(int x, double ext) {
    if (x == t)
        return ext;
    double flow, ret = 0;
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

inline double dinic(double mid) {
    double flow = tot = 0;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i)
        add(i, t, mid);
    for (int i = 1; i <= m; ++i) {
        add(s, n + i, 1);
        add(n + i, e[i].first, INF);
        add(n + i, e[i].second, INF);
    }
    while (bfs()) {
        memcpy(g, h, sizeof h);
        flow += dfs(s, INF);
    }
    return m - flow;
}

int main() {
    scanf("%d%d", &n, &m);
    if (!m) {
        printf("1\n1\n");
        return 0;
    }
    s = 0, t = n + m + 1;
    for (int i = 1; i <= m; ++i)
        scanf("%d%d", &e[i].first, &e[i].second);
    double l = 0, r = m;
    while (r - l > EPS) {
        double mid = (l + r) / 2;
        if (dinic(mid) > 0)
            l = mid;
        else
            r = mid;
    }
    dinic(l);
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        if (~d[i])
            ++cnt;
    printf("%d\n", cnt);
    for (int i = 1; i <= n; ++i)
        if (~d[i])
            printf("%d\n", i);
    return 0;
}
