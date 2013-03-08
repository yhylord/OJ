#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const double EPS = 1e-6;
const int MAXN = 111, MAXM = 888;

bool ans[MAXM];
double c[MAXM];
int tot, n, d[MAXN], q[MAXN], g[MAXN], h[MAXN], no[MAXM], p[MAXM], nxt[MAXM], u[MAXM], v[MAXM], w[MAXM];

inline void addedge(int x, int y, double z, int t) {
    p[tot] = y;
    c[tot] = z;
    no[tot] = t;
    nxt[tot] = h[x];
    h[x] = tot++;
}

inline bool bfs() {
    memset(d, -1, sizeof d);
    int r = d[q[0] = 1] = 0;
    for (int l = 0; l <= r; ++l)
        for (int k = h[q[l]]; ~k; k = nxt[k])
            if (c[k] && !~d[p[k]])
                d[q[++r] = p[k]] = d[q[l]] + 1;
    return ~d[n];
}

double dfs(int x, double ext) {
    if (x == n)
        return ext;
    double flow;
    for (int &k = g[x]; ~k; k = nxt[k])
        if (c[k] && d[p[k]] == d[x] + 1 && (flow = dfs(p[k], min(ext, c[k])))) {
            c[k] -= flow;
            c[k ^ 1] += flow;
            return flow;
        }
    return 0;
}

int main() {
    int m, cs = 0;
    while (scanf("%d%d", &n, &m) != EOF) {
        if (cs++)
            putchar('\n');
        double l = 0, r = 0;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &u[i], &v[i], &w[i]);
            if (w[i] > r)
                r = w[i];
        }
        while (r - l > EPS) {
            double mid = (l + r) / 2, cur = tot = 0, flow;
            memset(h, -1, sizeof h);
            for (int i = 0; i < m; ++i)
                if (w[i] - mid <= 0)
                    cur += w[i] - mid;
                else {
                    addedge(u[i], v[i], w[i] - mid, i);
                    addedge(v[i], u[i], w[i] - mid, i);
                }
            while (bfs()) {
                memcpy(g, h, sizeof h);
                while (flow = dfs(1, 1e10))
                    cur += flow;
            }
            if (cur > 0)
                l = mid;
            else
                r = mid;
        }
        double flow;
        int cnt = tot = 0, tmp = 0;
        memset(ans, false, sizeof ans);
        memset(h, -1, sizeof h);
        for (int i = 0; i < m; ++i)
            if (w[i] - l <= 0)
                cnt += ans[i] = true;
            else {
                addedge(u[i], v[i], w[i] - l, i);
                addedge(v[i], u[i], w[i] - l, i);
            }
        while (bfs()) {
            memcpy(g, h, sizeof h);
            while (flow = dfs(1, 1e10));
        }
        bfs();
        for (int i = 1; i <= n; ++i)
            if (~d[i])
                for (int k = h[i]; ~k; k = nxt[k])
                    if (!~d[p[k]])
                        cnt += ans[no[k]] = true;
        printf("%d\n", cnt);
        for (int i = 0; i < m; ++i)
            if (ans[i])
                if (++tmp == cnt)
                    printf("%d\n", i + 1);
                else
                    printf("%d ", i + 1);
    }
    return 0;
}
