#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 4444, MAXM = 22222, INF = 1000000000;

struct edge {
    int x, y, w;
} e[MAXN];

bool v[MAXN];
int tot, s, t, u[MAXM * 5], a[MAXN], d[MAXN], q[MAXN * MAXM], pre[MAXN],
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
        d[i] = -INF;
    int r = d[q[0] = s] = 0;
    v[s] = true;
    for (int l = 0; l <= r; ++l) {
        for (int k = h[q[l]]; ~k; k = nxt[k])
            if (c[k] && d[q[l]] + w[k] > d[p[k]]) {
                d[p[k]] = d[q[l]] + w[k];
                pre[p[k]] = k;
                if (!v[p[k]])
                    v[q[++r] = p[k]] = true;
            }
        v[q[l]] = false;
    }
    return d[t] > -INF;
}

inline int aug() {
    int flow = INF;
    for (int i = t; i != s; i = p[pre[i] ^ 1])
        flow = min(flow, c[pre[i]]);
    for (int i = t; i != s; i = p[pre[i] ^ 1]) {
        c[pre[i]] -= flow;
        c[pre[i] ^ 1] += flow;
    }
    return flow * d[t];
}

int main() {
    int n, k, ans = 0;
    scanf("%d%d", &n, &k);
    memset(h, -1, sizeof h);
    for (int i = 0; i < n; ++i) {
        int hh, mm, ss;
        scanf("%d:%d:%d", &hh, &mm, &ss);
        a[++a[0]] = e[i].x = hh * 3600 + mm * 60 + ss;
        scanf("%d:%d:%d%d", &hh, &mm, &ss, &e[i].w);
        a[++a[0]] = e[i].y = hh * 3600 + mm * 60 + ss;
    }
    sort(a + 1, a + a[0] + 1);
    a[0] = unique(a + 1, a + a[0] + 1) - a - 1;
    t = a[0] + 1;
    add(s, 1, k, 0);
    add(a[0], t, k, 0);
    for (int i = 1; i <= a[0]; ++i) {
        if (i < a[0])
            add(i, i + 1, INF, 0);
        u[a[i]] = i;
    }
    for (int i = 0; i < n; ++i)
        add(u[e[i].x], u[e[i].y], 1, e[i].w);
    while (spfa())
        ans += aug();
    printf("%d\n", ans);
    return 0;
}
