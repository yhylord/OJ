#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 222222, MAXM = 444444;

bool mk[MAXM], c[MAXN];
int tot, cur, size, goal, ans, a[MAXN], b[MAXN], t[MAXN], d[MAXN], e[MAXN],
    g[MAXN], s[MAXN], f[MAXN], h[MAXN], p[MAXM], w[MAXM], nxt[MAXM];

inline void addedge(int x, int y, int z) {
    p[tot] = y;
    w[tot] = z;
    mk[tot] = true;
    nxt[tot] = h[x];
    h[x] = tot++;
}

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

void findroot(int x, int pre) {
    s[x] = 1;
    g[x] = f[x] = 0;
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k] && p[k] != pre) {
            findroot(p[k], x);
            checkmax(g[x], g[p[k]]);
            s[x] += s[p[k]];
            checkmax(f[x], s[p[k]]);
        }
    g[x] += c[x];
    checkmax(f[x], size - s[x]);
    if (f[x] < f[cur])
        cur = x;
}

bool cmp(int x, int y) {
    return g[p[x]] > g[p[y]];
}

void dfs(int x, int pre) {
    if (e[x] <= goal)
        checkmax(a[e[x]], d[x]);
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k] && p[k] != pre) {
            e[p[k]] = e[x] + c[p[k]];
            d[p[k]] = d[x] + w[k];
            dfs(p[k], x);
        }
}

void work(int x) {
    findroot(x, t[0] = 0);
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k])
            t[++t[0]] = k;
    sort(t + 1, t + t[0] + 1, cmp);
    for (int i = max(goal - g[x], 0); i <= goal; ++i)
        b[i] = 0;
    goal -= c[x];
    for (int i = 1; i <= t[0]; ++i) {
        int k = t[i], hi = min(g[p[k]], goal), lo = goal - hi;
        e[p[k]] = c[p[k]];
        d[p[k]] = w[k];
        for (int j = 0; j <= hi; ++j)
            a[j] = 0;
        dfs(p[k], x);
        for (int j = 0; j <= hi; ++j)
            checkmax(ans, b[goal - j] + a[j]);
        int mx = 0;
        for (int j = 0; j <= hi; ++j) {
            checkmax(mx, a[j]);
            if (j >= lo)
                checkmax(b[j], mx);
        }
        for (int j = max(hi + 1, lo); j <= goal; ++j)
            checkmax(b[j], mx);
    }
    goal += c[x];
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k]) {
            mk[k ^ 1] = false;
            f[0] = size = s[p[k]];
            findroot(p[k], cur = 0);
            work(cur);
        }
}

int main() {
    int n, m;
    scanf("%d%d%d", &n, &goal, &m);
    memset(h, -1, sizeof h);
    while (m--) {
        int x;
        scanf("%d", &x);
        c[x] = true;
    }
    for (int i = 1; i < n; ++i) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addedge(x, y, z);
        addedge(y, x, z);
    }
    f[0] = size = n;
    findroot(1, cur = 0);
    work(cur);
    printf("%d\n", ans);
    return 0;
}
