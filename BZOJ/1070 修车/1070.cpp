#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 666, MAXM = 133333, INF = 1000000000;

bool v[MAXN];
int tot, s, t, pre[MAXN], d[MAXN], q[MAXN * MAXM / 10], h[MAXN], p[MAXM], c[MAXM], w[MAXM], nxt[MAXM];

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

inline int aug() {
    int flow = INF;
    for (int i = t; i != s; i = p[pre[i] ^ 1])
        flow = min(flow, c[pre[i]]);
    for (int i = t; i != s; i = p[pre[i] ^ 1]) {
        c[pre[i]] -= flow;
        c[pre[i] ^ 1] += flow;
    }
    return d[t] * flow;
}

int main() {
    int m, n, ans = 0;
    scanf("%d%d", &m, &n);
    t = (m + 1) * n + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i) {
        add(s, i, 1, 0);
        for (int j = 1; j <= m; ++j) {
            int x;
            scanf("%d", &x);
            add(j * n + i, t, 1, 0);
            for (int k = 1; k <= n; ++k)
                add(i, j * n + k, 1, x * k);
        }
    }
    while (spfa())
        ans += aug();
    printf("%.2lf\n", ans / double(n));
    return 0;
}
