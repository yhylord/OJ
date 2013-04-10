#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 11111, MAXM = 22222;

bool mk[MAXM];
int k, size, cur, tot, ans, a[MAXN], d[MAXN], s[MAXN], f[MAXN],
    h[MAXN], p[MAXM], w[MAXM], nxt[MAXM];

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

inline void addedge(int x, int y, int z) {
    p[tot] = y;
    w[tot] = z;
    nxt[tot] = h[x];
    mk[tot] = true;
    h[x] = tot++;
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

void dfs(int x, int pre) {
    s[x] = 1;
    a[++a[0]] = d[x];
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k] && p[k] != pre) {
            d[p[k]] = d[x] + w[k];
            dfs(p[k], x);
            s[x] += s[p[k]];
        }
}

inline int calc(int x, int init) {
    int ret = a[0] = 0;
    d[x] = init;
    dfs(x, 0);
    sort(a + 1, a + a[0] + 1);
    for (int l = 1, r = a[0]; l < r; )
        if (a[l] + a[r] <= k)
            ret += r - l++;
        else
            --r;
    return ret;
}

void work(int x) {
    ans += calc(x, 0);
    for (int k = h[x]; ~k; k = nxt[k])
        if (mk[k]) {
            mk[k ^ 1] = false;
            ans -= calc(p[k], w[k]);
            f[0] = size = s[p[k]];
            findroot(p[k], cur = 0);
            work(cur);
        }
}

int main() {
    int n;
    while (scanf("%d%d", &n, &k) && n) {
        tot = ans = 0;
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
        printf("%d\n", ans);
    }
    return 0;
}
