#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 111, MAXM = 5555, INF = 1000000000;

bool v[MAXN];
int tot, s, t, mx, ans, a[MAXN][MAXN], b[MAXN][MAXN], need[MAXN], pre[MAXN], d[MAXN],
    q[MAXN * MAXM], h[MAXN], p[MAXM], c[MAXM], w[MAXM], nxt[MAXM];

inline void addedge(int x, int y, int z, int r) {
    p[tot] = y;
    c[tot] = z;
    w[tot] = r;
    nxt[tot] = h[x];
    h[x] = tot++;
}

inline void add(int x, int y, int z, int r) {
    addedge(x, y, z, r);
    addedge(y, x, 0, -r);
}

inline bool spfa() {
    for (int i = 1; i <= t; ++i)
        d[i] = INF;
    int r = d[q[0] = s] = 0;
    v[s] = true;
    for (int l = 0; l <= r; ++l) {
        for (int k = h[q[l]]; ~k; k = nxt[k])
            if (c[k] && d[q[l]] + w[k] < d[p[k]]) {
                d[p[k]] = d[q[l]] + w[k];
                pre[p[k]] = k;
                if (!v[p[k]])
                    v[q[++r] = p[k]] = true;
            }
        v[q[l]] = false;
    }
    return d[t] < INF;
}

inline void aug() {
    int flow = INF;
    for (int i = t; i != s; i = p[pre[i] ^ 1])
        flow = min(flow, c[pre[i]]);
    for (int i = t; i != s; i = p[pre[i] ^ 1]) {
        c[pre[i]] -= flow;
        c[pre[i] ^ 1] += flow;
    }
    mx += flow;
    ans += flow * d[t];
}

int main() {
    int n, m, k;
    while (scanf("%d%d%d", &n, &m, &k) && n && m && k) {
        t = n + m + 1;
        ans = 0;
        memset(need, 0, sizeof need);
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < k; ++j) {
                scanf("%d", &a[i][j]);
                need[j] += a[i][j];
            }
        for (int i = 1; i <= m; ++i)
            for (int j = 0; j < k; ++j)
                scanf("%d", &b[i][j]);
        bool f = true;
        for (int u = 0; u < k; ++u) {
            memset(h, -1, sizeof h);
            tot = 0;
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= m; ++j) {
                    int x;
                    scanf("%d", &x);
                    add(i, n + j, INF, x);
                }
            if (!f)
                continue;
            for (int i = 1; i <= n; ++i)
                add(s, i, a[i][u], 0);
            for (int i = 1; i <= m; ++i)
                add(n + i, t, b[i][u], 0);
            mx = 0;
            while (spfa())
                aug();
            if (mx < need[u])
                f = false;
        }
        printf("%d\n", f ? ans : -1);
    }
    return 0;
}
