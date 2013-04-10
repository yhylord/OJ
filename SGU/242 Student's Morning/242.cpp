#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 444, MAXM = 88888, INF = 1000000000;

int tot, s, t, d[MAXN], q[MAXN], g[MAXN], h[MAXN], p[MAXM], c[MAXM], nxt[MAXM];

inline void addedge(int x, int y, int z) {
    p[tot] = y;
    c[tot] = z;
    nxt[tot] = h[x];
    h[x] = tot++;
}

inline void add(int x, int y, int z) {
    addedge(x, y, z);
    addedge(y, x, 0);
}

inline void set(int x, int y, int l, int r) {
    add(s, y, l);
    add(x, t, l);
    add(x, y, r - l);
}

inline bool bfs() {
    memset(d, -1, sizeof d);
    int r = d[q[0] = s] = 0;
    for (int l = 0; l <= r; ++l)
        for (int k = h[q[l]]; ~k; k = nxt[k])
            if (c[k] && !~d[p[k]])
                d[q[++r] = p[k]] = d[q[l]] + 1;
    return ~d[t];
}

int dfs(int x, int ext) {
    if (x == t)
        return ext;
    int flow, ret = 0;
    for (int &k = g[x]; ~k; k = nxt[k])
        if (c[k] && d[p[k]] == d[x] + 1 && (flow = dfs(p[k], min(c[k], ext)))) {
            ret += flow;
            c[k] -= flow;
            c[k ^ 1] += flow;
            if (!(ext -= flow))
                return ret;
        }
    return ret;
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int rs = 0, rt = n + k + 1;
    s = rt + 1, t = s + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i) {
        int x, y;
        for (scanf("%d", &x); x--; ) {
            scanf("%d", &y);
            add(i, n + y, 1);
        }
        add(rs, i, 1);
    }
    for (int i = 1; i <= k; ++i)
        set(n + i, rt, 2, INF);
    add(rt, rs, INF);
    int flow = 0;
    while (bfs()) {
        memcpy(g, h, sizeof h);
        flow += dfs(s, INF);
    }
    if (flow == k << 1) {
        puts("YES");
        for (int i = 1; i <= k; ++i) {
            int cnt = 0;
            for (int j = h[n + i]; ~j; j = nxt[j])
                if (p[j] <= n && c[j])
                    ++cnt;
            printf("%d", cnt);
            for (int j = h[n + i]; ~j; j = nxt[j])
                if (p[j] <= n && c[j])
                    printf(" %d", p[j]);
            puts("");
        }
    }
    else
        puts("NO");
    return 0;
}
