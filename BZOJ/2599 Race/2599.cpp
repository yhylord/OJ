#include <cstdio>
#include <cstring>

const int MAXN = 222222, MAXM = 444444, MAXC = 1111111;

bool mk[MAXM];
int tot, cur, size, ans, now, n, m, v[MAXC], c[MAXC], s[MAXN], f[MAXN],
    d[MAXN], e[MAXN], h[MAXN], p[MAXM], w[MAXM], nxt[MAXM];

inline void addedge(int x, int y, int z) {
    p[tot] = y;
    w[tot] = z;
    nxt[tot] = h[x];
    mk[tot] = true;
    h[x] = tot++;
}

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

inline void checkmin(int &x, int y) {
    if (y < x)
        x = y;
}

void findroot(int x, int pre) {
    s[x] = 1;
    f[x] = 0;
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k] && p[k] != pre) {
            findroot(p[k], x);
            s[x] += s[p[k]];
            checkmax(f[x], s[p[k]]);
        }
    checkmax(f[x], size - s[x]);
    if (f[x] < f[cur])
        cur = x;
}

void dfs1(int x, int pre) {
    if (d[x] > m)
        return;
    if (v[m - d[x]] == now)
        checkmin(ans, c[m - d[x]] + e[x]);
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k] && p[k] != pre) {
            d[p[k]] = d[x] + w[k];
            e[p[k]] = e[x] + 1;
            dfs1(p[k], x);
        }
}

void dfs2(int x, int pre) {
    if (d[x] > m)
        return;
    if (v[d[x]] != now) {
        c[d[x]] = e[x];
        v[d[x]] = now;
    }
    else
        checkmin(c[d[x]], e[x]);
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k] && p[k] != pre)
            dfs2(p[k], x);
}

void work(int x) {
    v[0] = now = x + 1;
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k]) {
            d[p[k]] = w[k];
            e[p[k]] = 1;
            dfs1(p[k], x);
            dfs2(p[k], x);
        }
    findroot(x, n);
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k]) {
            mk[k ^ 1] = false;
            f[n] = size = s[p[k]];
            findroot(p[k], cur = n);
            work(cur);
        }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; ++i) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addedge(x, y, z);
        addedge(y, x, z);
    }
    ans = f[n] = size = n;
    findroot(0, cur = n);
    work(cur);
    printf("%d\n", ans < n ? ans : -1);
    return 0;
}
