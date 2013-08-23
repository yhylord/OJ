#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 222222, MAXM = 1111111, INF = 1000000000;

int node, tot, cnt, s, t, root[MAXN], l[MAXN], r[MAXN], idx[MAXN],
    d[MAXN], q[MAXN], g[MAXN], h[MAXN], p[MAXM], c[MAXM], nxt[MAXM];

inline void addedge(int x, int y, int z) {
    p[tot] = y, c[tot] = z, nxt[tot] = h[x], h[x] = tot++;
}

inline void add(int x, int y, int z) {
    addedge(x, y, z), addedge(y, x, 0);
}

void query(int x, int f, int t, int qf, int qt, int id) {
    if (!x)
        return;
    if (qf <= f && t <= qt) {
        add(id, idx[x], INF);
        return;
    }
    int mid = f + t >> 1;
    if (qf <= mid)
        query(l[x], f, mid, qf, qt, id);
    if (qt > mid)
        query(r[x], mid + 1, t, qf, qt, id);
}

void insert(int x, int &y, int f, int t, int v, int id) {
    add(idx[y = node++] = cnt++, idx[x], INF);
    if (f == t) {
        add(idx[y], id, INF);
        return;
    }
    int mid = f + t >> 1;
    if (v <= mid) {
        r[y] = r[x];
        insert(l[x], l[y], f, mid, v, id);
        add(idx[y], idx[l[y]], INF);
    }
    else {
        l[y] = l[x];
        insert(r[x], r[y], mid + 1, t, v, id);
        add(idx[y], idx[r[y]], INF);
    }
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

int dfs(int x, int ext) {
    if (x == t)
        return ext;
    int flow, ret = 0;
    for (int &k = g[x]; ~k; k = nxt[k])
        if (c[k] && d[p[k]] == d[x] + 1 && (flow = dfs(p[k], min(c[k], ext)))) {
            ret += flow, c[k] -= flow, c[k ^ 1] += flow;
            if (!(ext -= flow))
                return ret;
        }
    return ret;
}

int main() {
    int n, ans = 0;
    scanf("%d", &n);
    s = 0, t = node = 1, cnt = n + n + 2;
    memset(h, -1, sizeof h);
    for (int i = 2; i <= n + 1; ++i) {
        int a, b, w, l, r, p;
        scanf("%d%d%d%d%d%d", &a, &b, &w, &l, &r, &p);
        ans += b + w;
        add(s, i, b), add(i, t, w), add(i, i + n, p);
        query(root[i - 2], 0, INF, l, r, i + n);
        insert(root[i - 2], root[i - 1], 0, INF, a, i);
    }
    while (bfs()) {
        memcpy(g, h, sizeof h);
        ans -= dfs(s, INF);
    }
    printf("%d\n", ans);
    return 0;
}
