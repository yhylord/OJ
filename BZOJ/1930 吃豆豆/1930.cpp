#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 4444, MAXM = 4111111;

bool v[MAXN];
int tot, s, t, f[MAXN], pre[MAXN], d[MAXN], q[MAXN], h[MAXN], p[MAXM], c[MAXM], w[MAXM], nxt[MAXM];
pair<int, int> a[MAXN];

inline void addedge(int x, int y, int z, int r) {
    p[tot] = y, c[tot] = z, w[tot] = r, nxt[tot] = h[x], h[x] = tot++;
}

inline void add(int x, int y, int z, int r) {
    addedge(x, y, z, r), addedge(y, x, 0, -r);
}

inline void inc(int &x) {
    if (++x == MAXN)
        x = 0;
}

inline int spfa() {
    memset(d, -63, sizeof d);
    memset(v, false, sizeof v);
    d[q[0] = s] = 0;
    v[s] = true;
    for (int l = 0, r = 1; l != r; inc(l)) {
        for (int k = h[q[l]]; ~k; k = nxt[k])
            if (c[k] && d[q[l]] + w[k] > d[p[k]]) {
                d[p[k]] = d[q[l]] + w[k];
                if (!v[p[k]])
                    v[q[r] = p[k]] = true, inc(r);
            }
        v[q[l]] = false;
    }
    return d[t];
}

int main() {
    int n, goal = 0;
    scanf("%d", &n);
    s = (n << 1) + 1, t = s + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &a[i].first, &a[i].second);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < n; ++j)
            if (a[j].second <= a[i].second && f[j] > f[i])
                f[i] = f[j], pre[i] = j;
        if (++f[i] > f[goal])
            goal = i;
    }
    for (int i = goal; i; i = pre[i])
        v[i] = true;
    add(s, 0, 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (v[i])
            add(i, i + n, 1, 0);
        else
            add(i + n, i, 1, 0);
        if (i == goal)
            add(t, i, 1, 0);
        else
            add(i, t, 1, 0);
        for (int j = 0; j < i; ++j)
            if (a[i].second >= a[j].second)
                if (v[i] && pre[i] == j)
                    add(i + n, j, 1, -1);
                else
                    add(j, i + n, 1, 1);
    }
    printf("%d\n", f[goal] + spfa());
    return 0;
}
