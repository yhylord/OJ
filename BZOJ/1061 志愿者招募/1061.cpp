#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 1111, MAXM = 33333, INF = 1000000000;

bool v[MAXN];
int tot, s, t, a[MAXN], d[MAXN], q[MAXN * MAXM / 10], pre[MAXN],
    h[MAXN], p[MAXM], c[MAXM], w[MAXM], nxt[MAXM];

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
    int n, m, ans = 0;
    scanf("%d%d", &n, &m);
    t = n + 2;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n + 1; ++i) {
        if (i <= n)
            add(i, i + 1, INF, 0);
        if (a[i] - a[i - 1] < 0)
            add(s, i, a[i - 1] - a[i], 0);
        else
            add(i, t, a[i] - a[i - 1], 0);
    }
    while (m--) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(y + 1, x, INF, z);
    }
    while (spfa())
        ans += aug();
    printf("%d\n", ans);
    return 0;
}
