#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 555, MAXM = 3333, INF = 1000000000;

bool v[MAXN];
int tot, s, t, n, m, deg[MAXN], d[MAXN], q[MAXN * MAXM], pre[MAXN],
    h[MAXN], p[MAXM], c[MAXM], w[MAXM], nxt[MAXM];

inline int no(int x, int y) {
    return x * m + y;
}

inline void addedge(int x, int y, int z, int r) {
    p[tot] = y, c[tot] = z, w[tot] = r, nxt[tot] = h[x], h[x] = tot++;
}

inline void add(int x, int y, int z, int r) {
    addedge(x, y, z, r), addedge(y, x, 0, -r);
}

inline bool spfa() {
    for (int i = 0; i <= t; ++i)
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
    for (int i = t; i != s; i = p[pre[i] ^ 1])
        c[pre[i]] -= flow, c[pre[i] ^ 1] += flow;
    return flow * d[t];
}

int main() {
    scanf("%d%d", &n, &m);
    int cnt = n * m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n; ++i) {
        scanf(" ");
        for (int j = 0; j < m; ++j) {
            char c = getchar();
            int x = no(i, j), y = cnt++,
                u = no((i - 1 + n) % n, j), d = no((i + 1) % n, j),
                l = no(i, (j - 1 + m) % m), r = no(i, (j + 1) % m);
            --deg[x];
            if (c == 'U') {
                ++deg[u];
                add(u, y, 1, 0), add(y, d, 1, 1);
                add(y, l, 1, 1), add(y, r, 1, 1);
            }
            else if (c == 'D') {
                ++deg[d];
                add(d, y, 1, 0), add(y, u, 1, 1);
                add(y, l, 1, 1), add(y, r, 1, 1);
            }
            else if (c == 'L') {
                ++deg[l];
                add(l, y, 1, 0), add(y, r, 1, 1);
                add(y, u, 1, 1), add(y, d, 1, 1);
            }
            else {
                ++deg[r];
                add(r, y, 1, 0), add(y, l, 1, 1);
                add(y, u, 1, 1), add(y, d, 1, 1);
            }
        }
    }
    s = cnt, t = cnt + 1;
    for (int i = 0; i < n * m; ++i)
        if (deg[i] > 0)
            add(s, i, deg[i], 0);
        else if (deg[i] < 0)
            add(i, t, -deg[i], 0);
    int ans = 0;
    while (spfa())
        ans += aug();
    printf("%d\n", ans);
    return 0;
}
