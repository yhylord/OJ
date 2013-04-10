#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 1111, MAXM = 8888, INF = 1000000000;

bool v[MAXN];
int tot, s, t, d[MAXN], q[MAXN * MAXM], pre[MAXN], h[MAXN], p[MAXM], c[MAXM], w[MAXM], nxt[MAXM];

inline void addedge(int x, int y, int z, int r) {
    p[tot] = y;
    c[tot] = z;
    w[tot] = r;
    nxt[tot] = h[x];
    h[x] = tot++;
}

inline bool spfa() {
    v[q[0] = s] = true;
    for (int i = 0; i <= t; ++i)
        d[i] = INF;
    d[s] = 0;
    int r = 0;
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
    int cs;
    scanf("%d", &cs);
    while (cs--) {
        int n, ans = 0;
        scanf("%d", &n);
        s = n;
        t = n + 1;
        tot = 0;
        memset(h, -1, sizeof h);
        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);
            addedge(s, i, x, 0);
            addedge(i, s, 0, 0);
            addedge(i, t, 1, 0);
            addedge(t, i, 0, 0);
            addedge(i, (i - 1 + n) % n, INF, 1);
            addedge((i - 1 + n) % n, i, 0, -1);
            addedge(i, (i + 1) % n, INF, 1);
            addedge((i + 1) % n, i, 0, -1);
        }
        while (spfa())
            ans += aug();
        printf("%d\n", ans);
    }
    return 0;
}
