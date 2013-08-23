#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 555, MAXM = 66666;

int n, m, p, s[MAXN][MAXN], b[MAXM], c1[MAXM], c2[MAXM], ans[MAXM];

struct data {
    int v, x, y;
} a[MAXN * MAXN];

struct query {
    int x1, y1, x2, y2, k;
} q[MAXM];

inline bool operator <(const data &x, const data &y) {
    return x.v < y.v;
}

inline void add(int x, int y, int v) {
    for (; x <= n; x += x & -x)
        for (int ty = y; ty <= n; ty += ty & -ty)
            s[x][ty] += v;
}

inline int sum(int x, int y) {
    int ret = 0;
    for (; x; x -= x & -x)
        for (int ty = y; ty; ty -= ty & -ty)
            ret += s[x][ty];
    return ret;
}

void solve(int l, int r, int f, int t, int bg) {
    if (f > t)
        return;
    if (l == r) {
        for (int i = f; i <= t; ++i)
            ans[b[i]] = l;
        return;
    }
    int mid = l + r >> 1, ed = bg;
    for (; ed <= p && a[ed].v <= mid; ++ed)
        add(a[ed].x, a[ed].y, 1);
    c1[0] = c2[0] = 0;
    for (int i = f; i <= t; ++i)
        if (q[b[i]].k <= sum(q[b[i]].x2, q[b[i]].y2) + sum(q[b[i]].x1 - 1, q[b[i]].y1 - 1) - sum(q[b[i]].x1 - 1, q[b[i]].y2) - sum(q[b[i]].x2, q[b[i]].y1 - 1))
            c1[++c1[0]] = b[i];
        else
            c2[++c2[0]] = b[i];
    for (int i = 1; i <= c1[0]; ++i)
        b[f + i - 1] = c1[i];
    for (int i = 1; i <= c2[0]; ++i)
        b[f + c1[0] + i - 1] = c2[i];
    int cnt = c1[0];
    solve(mid + 1, r, f + cnt, t, ed);
    for (int i = bg; i < ed; ++i)
        add(a[i].x, a[i].y, -1);
    solve(l, mid, f, f + cnt - 1, bg);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &a[++p].v);
            a[p].x = i, a[p].y = j;
        }
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d%d%d", &q[i].x1, &q[i].y1, &q[i].x2, &q[i].y2, &q[b[i] = i].k);
    sort(a + 1, a + p + 1);
    solve(0, 1000000000, 1, m, 1);
    for (int i = 1; i <= m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
