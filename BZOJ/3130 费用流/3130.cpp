#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

const double EPS = 1e-6, INF = 1e10;
const int MAXN = 111, MAXM = 2222;

struct edge {
    double c;
    int a, b;
} e[MAXM];

double c[MAXM];
int tot, s, t, m, d[MAXN], q[MAXN], g[MAXN], h[MAXN], p[MAXM], nxt[MAXM];

inline void addedge(int x, int y, double z) {
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

double dfs(int x, double ext) {
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

inline double dinic(double lim) {
    double ret = 0;
    tot = 0;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; ++i) {
        addedge(e[i].a, e[i].b, min(lim, e[i].c));
        addedge(e[i].b, e[i].a, 0);
    }
    while (bfs()) {
        memcpy(g, h, sizeof h);
        ret += dfs(s, INF);
    }
    return ret;
}

int main() {
    double l = 0, r = 0;
    int n, p;
    scanf("%d%d%d", &n, &m, &p);
    s = 1, t = n;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%lf", &e[i].a, &e[i].b, &e[i].c);
        r = max(r, e[i].c);
    }
    double ans = dinic(r);
    while (r - l > EPS) {
        double mid = (l + r) / 2;
        if (fabs(dinic(mid) - ans) < EPS)
            r = mid;
        else
            l = mid;
    }
    printf("%.0lf\n%.4lf\n", ans, p * r);
    return 0;
}
