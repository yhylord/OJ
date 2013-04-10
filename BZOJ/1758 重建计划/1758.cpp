#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const double EPS = 1e-4;
const int MAXN = 111111, MAXM = 222222;

bool mk[MAXM];
double ans, l, r, mid, d[MAXN], a[MAXN], b[MAXN];
int tot, size, cur, low, upp, e[MAXN], g[MAXN], t[MAXN], q[MAXN],
    s[MAXN], f[MAXN], h[MAXN], p[MAXM], w[MAXM], nxt[MAXM];

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

inline void checkmax(double &x, double y) {
    if (y > x)
        x = y;
}

void findroot(int x, int pre) {
    s[x] = 1;
    g[x] = f[x] = 0;
    bool t = false;
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k] && p[k] != pre) {
            t = true;
            findroot(p[k], x);
            checkmax(g[x], g[p[k]]);
            s[x] += s[p[k]];
            checkmax(f[x], s[p[k]]);
            checkmax(r, w[k]);
            if (w[k] < l)
                l = w[k];
        }
    g[x] += t;
    checkmax(f[x], size - s[x]);
    if (f[x] < f[cur])
        cur = x;
}

void dfs(int x, int pre) {
    if (e[x] <= upp)
        checkmax(a[e[x]], d[x]);
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k] && p[k] != pre) {
            e[p[k]] = e[x] + 1;
            d[p[k]] = d[x] + w[k] - mid;
            dfs(p[k], x);
        }
}

bool cmp(int x, int y) {
    return g[p[x]] > g[p[y]];
}

void work(int x) {
    l = 1e12;
    r = 0;
    findroot(x, t[0] = 0);
    if (s[x] <= low)
        return;
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k])
            t[++t[0]] = k;
    sort(t + 1, t + t[0] + 1, cmp);
    while (r - l > EPS) {
        mid = (l + r) / 2;
        double mx = -1e12;
        for (int i = max(upp - g[x], 0); i <= upp; ++i)
            b[i] = i <= upp - low ? 0 : -1e12;
        for (int i = 1; i <= t[0]; ++i) {
            int k = t[i], hi = min(g[p[k]] + 1, upp), lo = upp - hi;
            e[p[k]] = 1;
            d[p[k]] = w[k] - mid;
            for (int j = 0; j <= hi; ++j)
                a[j] = -1e12;
            dfs(p[k], x);
            for (int j = 0; j <= hi; ++j)
                checkmax(mx, b[upp - j] + a[j]);
            int f = 0, t = -1;
            for (int j = 0; j <= hi; ++j) {
                for (; f <= t && j - q[f] > upp - low; ++f);
                for (; f <= t && a[j] > a[q[t]]; --t);
                q[++t] = j;
                if (f <= t && j >= lo)
                    checkmax(b[j], a[q[f]]);
            }
            for (int j = max(hi + 1, lo); j <= upp; ++j) {
                for (; f <= t && j - q[f] > upp - low; ++f);
                if (f <= t)
                    checkmax(b[j], a[q[f]]);
            }
        }
        if (mx > 0)
            l = mid;
        else
            r = mid;
    }
    checkmax(ans, l);
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k]) {
            mk[k ^ 1] = false;
            f[0] = size = s[p[k]];
            findroot(p[k], cur = 0);
            work(cur);
        }
}

int main() {
    int n;
    scanf("%d%d%d", &n, &low, &upp);
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; ++i) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addedge(x, y, z);
        addedge(y, x, z);
    }
    f[0] = size = n;
    findroot(1, cur = 0);
    work(cur);
    printf("%.3lf\n", ans);
    return 0;
}
