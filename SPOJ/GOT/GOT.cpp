#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 111111;

int m, tot, size, h[MAXN], p[MAXN << 1], nxt[MAXN << 1], lg[MAXN], a[MAXN], b[MAXN],
    d[MAXN], f[MAXN][18], root[MAXN], s[MAXN * 18], l[MAXN * 18], r[MAXN * 18];

void insert(int x, int &y, int f, int t, int v) {
    s[y = ++size] = s[x] + 1;
    if (f == t) {
        l[y] = r[y] = 0;
        return;
    }
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

int query(int x, int y, int p, int q, int f, int t, int v) {
    if (f == t)
        return s[x] + s[y] - s[p] - s[q];
    int mid = f + t >> 1;
    if (v <= mid)
        return query(l[x], l[y], l[p], l[q], f, mid, v);
    return query(r[x], r[y], r[p], r[q], mid + 1, t, v);
}

inline void addedge(int x, int y) {
    p[++tot] = y;
    nxt[tot] = h[x];
    h[x] = tot;
}

void dfs(int x, int dep) {
    insert(root[f[x][0]], root[x], 1, m, lower_bound(b + 1, b + m + 1, a[x]) - b);
    d[x] = dep;
    for (int k = 1; k <= lg[dep]; ++k)
        f[x][k] = f[f[x][k - 1]][k - 1];
    for (int k = h[x]; k; k = nxt[k])
        if (!~d[p[k]]) {
            f[p[k]][0] = x;
            dfs(p[k], dep + 1);
        }
}

inline int lca(int x, int y) {
    if (d[x] > d[y])
        swap(x, y);
    while (d[y] > d[x])
        y = f[y][lg[d[y] - d[x]]];
    if (x == y)
        return x;
    for (int k = lg[d[x]]; k >= 0; --k)
        if (f[x][k] != f[y][k]) {
            x = f[x][k];
            y = f[y][k];
        }
    return f[x][0];
}

int main() {
    for (int i = 2; i < MAXN; ++i)
        lg[i] = lg[i - 1] + (1 << lg[i - 1] + 1 == i);
    int n, q;
    while (scanf("%d%d", &n, &q) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            b[i] = a[i];
        }
        sort(b + 1, b + n + 1);
        m = unique(b + 1, b + n + 1) - b - 1;
        memset(h, tot = size = 0, sizeof h);
        for (int i = 1; i < n; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            addedge(x, y);
            addedge(y, x);
        }
        memset(d, -1, sizeof d);
        dfs(1, 0);
        while (q--) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            int t = lca(x, y), v = lower_bound(b + 1, b + m + 1, z) - b;
            puts(b[v] == z && query(root[x], root[y], root[t], root[f[t][0]], 1, m, v) ? "Find" : "NotFind");
        }
        puts("");
    }
    return 0;
}
