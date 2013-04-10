#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 111111, MAXT = 1811111;

int tot, h[MAXN], p[MAXN << 1], nxt[MAXN << 1], f[MAXN][18], d[MAXN], lg[MAXN],
    size, m, a[MAXN], b[MAXN], root[MAXN], l[MAXT], r[MAXT], s[MAXT];

inline void addedge(int u, int v) {
    p[++tot] = v;
    nxt[tot] = h[u];
    h[u] = tot;
}

void insert(int x, int &y, int f, int t, int v) {
    s[y = ++size] = s[x] + 1;
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
    int mid = f + t >> 1, cur = s[l[x]] + s[l[y]] - s[l[z1]] - s[l[z2]];
    if (v <= cur)
        return query(l[x], l[y], l[z1], l[z2], f, mid, v);
    return query(r[x], r[y], r[z1], r[z2], mid + 1, t, v - cur);
}

void dfs(int u, int dep) {
    d[u] = dep + 1;
    insert(root[f[u][0]], root[u], 1, m, lower_bound(b + 1, b + m + 1, a[u]) - b);
    for (int k = 1; k <= lg[dep]; ++k)
        f[u][k] = f[f[u][k - 1]][k - 1];
    for (int k = h[u]; k; k = nxt[k])
        if (!d[p[k]]) {
            f[p[k]][0] = u;
            dfs(p[k], dep + 1);
        }
}

inline int lca(int u, int v) {
    if (d[u] > d[v])
        swap(u, v);
    while (d[v] > d[u])
        v = f[v][lg[d[v] - d[u]]];
    if (u == v)
        return u;
    for (int k = lg[d[u] - 1]; k >= 0; --k)
        if (f[u][k] != f[v][k]) {
            u = f[u][k];
            v = f[v][k];
        }
    return f[u][0];
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        b[i] = a[i];
        lg[i] = lg[i - 1] + (i == 1 << lg[i - 1] + 1);
    }
    sort(b + 1, b + n + 1);
    m = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    dfs(1, 0);
    while (q--) {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        int c = lca(u, v);
        printf("%d\n", b[query(root[u], root[v], root[c], root[f[c][0]], 1, m, k)]);
    }
    return 0;
}
