#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 444, MAXM = 44444, INF = 1000000000;

bool v[MAXN];
int mx, ans, tot, s, t, pre[MAXN], d[MAXN], q[MAXN * MAXM / 10], h[MAXN], p[MAXM], c[MAXM], w[MAXM], nxt[MAXM];

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
    int n, m;
    scanf("%d%d", &n, &m);
    t = n + n + 1;
    memset(h, -1, sizeof h);
    add(s, n + 1, INF, 0);
    add(n, t, INF, 0);
    for (int i = 1; i <= n; ++i)
        add(i, i + n, 1, 0);
    while (m--) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x + n, y, 1, z);
    }
    while (spfa())
        aug();
    printf("%d %d\n", mx, ans);
    return 0;
}
