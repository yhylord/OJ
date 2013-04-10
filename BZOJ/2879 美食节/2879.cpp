#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 1111, MAXM = 77777, INF = 1000000000;

bool v[MAXN];
int tot, s, t, a[MAXN][MAXN], cnt[MAXN], cur[MAXN], pre[MAXN], d[MAXN],
    q[MAXN * MAXM / 10], h[MAXN], p[MAXM], c[MAXM], w[MAXM], nxt[MAXM];

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

inline void spfa() {
    for (int i = 1; i <= t; ++i)
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
}

int main() {
    int n, m, sp = 0, ans = 0;
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        sp += x;
        add(s, i, x, 0);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
            add(i, n + j, 1, a[i][j]);
        }
    t = n + m + sp + 1;
    for (int i = 1; i <= m; ++i) {
        cnt[i] = 1;
        add(n + i, t, 1, 0);
        cur[i] = tot - 2;
    }
    for (int k = 1; k <= sp; ++k) {
        spfa();
        for (int i = t; i != s; i = p[pre[i] ^ 1]) {
            --c[pre[i]];
            ++c[pre[i] ^ 1];
        }
        ans += d[t];
        int x = 1;
        for (; x <= m && c[cur[x]]; ++x);
        ++cnt[x];
        for (int i = 1; i <= n; ++i)
            add(i, n + m + k, 1, a[i][x] * cnt[x]);
        add(n + m + k, t, 1, 0);
        cur[x] = tot - 2;
    }
    printf("%d\n", ans);
    return 0;
}
