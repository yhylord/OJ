#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

const double INF = 20;
const int MAXN = 111, MAXM = 2222;

double c[MAXM];
int tot, s, t, d[MAXN], q[MAXN], g[MAXN], h[MAXN], p[MAXM], nxt[MAXM];

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
    double flow;
    for (int &k = g[x]; ~k; k = nxt[k])
        if (c[k] && d[p[k]] == d[x] + 1 && (flow = dfs(p[k], min(c[k], ext)))) {
            c[k] -= flow;
            c[k ^ 1] += flow;
            return flow;
        }
    return 0;
}

int main() {
    int cs;
    scanf("%d", &cs);
    while (cs--) {
        int n, m, l;
        scanf("%d%d%d", &n, &m, &l);
        tot = 0;
        t = n + m + 1;
        memset(h, -1, sizeof h);
        for (int i = 1; i <= n; ++i) {
            double x;
            scanf("%lf", &x);
            addedge(s, i, log(x));
            addedge(i, s, 0);
        }
        for (int i = 1; i <= m; ++i) {
            double x;
            scanf("%lf", &x);
            addedge(n + i, t, log(x));
            addedge(t, n + i, 0);
        }
        while (l--) {
            int x, y;
            scanf("%d%d", &x, &y);
            addedge(x, n + y, INF);
            addedge(n + y, x, 0);
        }
        double ans = 0;
        while (bfs()) {
            double flow;
            memcpy(g, h, sizeof h);
            while (flow = dfs(s, INF))
                ans += flow;
        }
        printf("%.4f\n", exp(ans));
    }
    return 0;
}
