#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 88888, MAXT = MAXN * 20;

int a[MAXN], b[MAXN], c[MAXN], lg[MAXN], e[MAXN], f[MAXN][20], u,
    q[MAXN], size[MAXN], be[MAXN], node[MAXN], d[MAXT], l[MAXT], r[MAXT], tsize,
    h[MAXN], p[MAXN << 2], nxt[MAXN << 2], tot;

inline void addedge(int x, int y) {
    p[++tot] = y;
    nxt[tot] = h[x];
    h[x] = tot;
}

void insert(int x, int &y, int f, int t, int v) {
    if (!y)
        y = ++tsize;
    d[y] = d[x] + 1;
    if (f == t)
        return;
    int mid = f + t >> 1;
    if (v <= mid) {
        r[y] = r[x];
        insert(l[x], l[y], f, mid, v);
    }
    else {
        l[y] = l[x];
        insert(r[x], r[y], mid + 1, t, v);
    }
}

int query(int x, int y, int z1, int z2, int f, int t, int v) {
    if (f == t)
        return f;
    int mid = f + t >> 1, cur = d[l[x]] + d[l[y]] - d[l[z1]] - d[l[z2]];
    if (v <= cur)
        return query(l[x], l[y], l[z1], l[z2], f, mid, v);
    return query(r[x], r[y], r[z1], r[z2], mid + 1, t, v - cur);
}

inline void bfs(int x, int bg, int ed, int fr) {
    int r = 0;
    f[q[0] = x][0] = fr;
    for (int l = 0; l <= r; ++l) {
        ++size[be[x = q[l]] = ed];
        if (f[x][0])
            e[x] = e[f[x][0]] + 1;
        insert(node[f[x][0]], node[x], 1, u, c[x]);
        for (int k = 1; k <= lg[e[x]]; ++k)
            f[x][k] = f[f[x][k - 1]][k - 1];
        for (int k = lg[e[x]] + 1; k < 20; ++k)
            f[x][k] = 0;
        for (int k = h[x]; k; k = nxt[k])
            if (be[p[k]] == bg)
                f[q[++r] = p[k]][0] = x;
    }
}

inline int lca(int x, int y) {
    for (; e[y] > e[x]; y = f[y][lg[e[y] - e[x]]]);
    for (; e[x] > e[y]; x = f[x][lg[e[x] - e[y]]]);
    if (x == y)
        return x;
    for (int k = lg[e[x]]; k >= 0; --k)
        if (f[x][k] != f[y][k]) {
            x = f[x][k];
            y = f[y][k];
        }
    return f[x][0];
}

int main() {
    int n, m, t, cnt = 0, lst = 0;
    scanf("%*d%d%d%d", &n, &m, &t);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        b[i] = a[i];
        lg[i] = lg[i - 1] + (1 << lg[i - 1] + 1 == i);
    }
    sort(b + 1, b + n + 1);
    u = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; ++i)
        c[i] = lower_bound(b + 1, b + u + 1, a[i]) - b;
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y);
        addedge(y, x);
    }
    for (int i = 1; i <= n; ++i)
        if (!be[i])
            bfs(i, 0, ++cnt, 0);
    while (t--) {
        char op;
        int x, y;
        scanf(" %c%d%d", &op, &x, &y);
        x ^= lst, y ^= lst;
        if (op == 'L') {
            if (size[be[x]] < size[be[y]])
                swap(x, y);
            bfs(y, be[y], be[x], x);
            addedge(x, y);
            addedge(y, x);
        }
        else {
            int k, z = lca(x, y);
            scanf("%d", &k);
            printf("%d\n", lst = b[query(node[x], node[y], node[z], node[f[z][0]], 1, u, k ^ lst)]);
        }
    }
    return 0;
}
