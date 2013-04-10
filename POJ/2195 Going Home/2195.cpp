#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAXN = 222, MAXM = 22222, INF = 1000000000;

bool v[MAXN];
int tot, s, t, n, m, pre[MAXN], d[MAXN], q[MAXN * MAXM], h[MAXN], p[MAXM], c[MAXM], w[MAXM], nxt[MAXM];
pair<int, int> peo[MAXN], hou[MAXN];

inline int no(int x, int y) {
    return (x - 1) * m + y;
}

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
    for (int i = t; i != s; i = p[pre[i] ^ 1]) {
        c[pre[i]] -= flow;
        c[pre[i] ^ 1] += flow;
    }
    return d[t] * flow;
}

int main() {
    while (scanf("%d%d", &n, &m) && n && m) {
        peo[0].first = hou[0].first = tot = 0;
        memset(h, -1, sizeof h);
        for (int i = 1; i <= n; ++i) {
            scanf(" ");
            for (int j = 1; j <= m; ++j) {
                char c = getchar();
                if (c == 'H')
                    hou[++hou[0].first] = make_pair(i, j);
                else if (c == 'm')
                    peo[++peo[0].first] = make_pair(i, j);
            }
        }
        t = peo[0].first + hou[0].first + 1;
        for (int i = 1; i <= peo[0].first; ++i)
            add(s, i, 1, 0);
        for (int i = 1; i <= hou[0].first; ++i)
            add(peo[0].first + i, t, 1, 0);
        for (int i = 1; i <= peo[0].first; ++i)
            for (int j = 1; j <= hou[0].first; ++j)
                add(i, peo[0].first + j, 1, abs(peo[i].first - hou[j].first) + abs(peo[i].second - hou[j].second));
        int ans = 0;
        while (spfa())
            ans += aug();
        printf("%d\n", ans);
    }
    return 0;
}
