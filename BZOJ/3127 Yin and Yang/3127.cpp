#include <cstdio>
#include <cstring>

const int STD = 111111, MAXN = 222222;

bool mk[MAXN];
int tot, now, idx, size, cur, n, u[MAXN], v1[MAXN], v2[MAXN], c1[MAXN], c2[MAXN],
    f[MAXN], s[MAXN], d[MAXN], h[MAXN], p[MAXN], w[MAXN], nxt[MAXN];
long long ans;

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
    f[x] = 0;
    s[x] = 1;
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k] && p[k] != pre) {
            d[p[k]] = d[x] + w[k];
            findroot(p[k], x);
            s[x] += s[p[k]];
            checkmax(f[x], s[p[k]]);
        }
    checkmax(f[x], size - s[x]);
    if (f[x] < f[cur])
        cur = x;
}

void dfs1(int x, int pre) {
    int t = u[d[x]];
    if (u[d[x]] != idx) {
        u[d[x]] = idx;
        if (v1[d[x]] != now) {
            v1[d[x]] = now;
            c1[d[x]] = 1;
        }
        else
            ++c1[d[x]];
    }
    else
        if (v2[d[x]] != now) {
            v2[d[x]] = now;
            c2[d[x]] = 1;
        }
        else
            ++c2[d[x]];
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k] && p[k] != pre)
            dfs1(p[k], x);
    u[d[x]] = t;
}

void dfs2(int x, int pre, bool fnd) {
    int t = u[d[x]], nd = (STD << 1) - d[x];
    if (u[d[x]] != idx) {
        u[d[x]] = idx;
        ans += (v2[nd] == now ? c2[nd] : 0) + (d[x] == STD && fnd);
    }
    else
        ans += (v1[nd] == now ? c1[nd] : 0) + (v2[nd] == now ? c2[nd] : 0) + (d[x] == STD && fnd);
    if (d[x] == STD)
        fnd = true;
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k] && p[k] != pre)
            dfs2(p[k], x, fnd);
    u[d[x]] = t;
}

void work(int x) {
    d[now = x] = STD;
    findroot(x, 0);
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k]) {
            u[STD] = idx = k + 1;
            dfs2(p[k], x, false);
            idx = n + n + k + 1;
            dfs1(p[k], x);
        }
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k]) {
            mk[k ^ 1] = false;
            f[0] = size = s[p[k]];
            findroot(p[k], cur = 0);
            work(cur);
        }
}

int main() {
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; ++i) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        if (!z)
            z = -1;
        addedge(x, y, z);
        addedge(y, x, z);
    }
    f[0] = size = n;
    findroot(1, cur = 0);
    work(cur);
    printf("%lld\n", ans);
    return 0;
}
