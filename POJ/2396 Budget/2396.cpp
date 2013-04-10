#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 333, MAXM = 33333, INF = 1000000000;

int tot, sum, s, t, lo[MAXN][MAXN], hi[MAXN][MAXN], d[MAXN], q[MAXN],
    g[MAXN], h[MAXN], p[MAXM], c[MAXM], nxt[MAXM];

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
    sum += l;
    add(s, y, l);
    add(x, t, l);
    if (r > l)
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
    int cs;
    scanf("%d", &cs);
    while (cs--) {
        int n, m, u;
        scanf("%d%d", &n, &m);
        int rs = tot = sum = 0, rt = n + m + 1;
        s = rt + 1, t = s + 1;
        memset(h, -1, sizeof h);
        for (int i = 1; i <= n; ++i) {
            int x;
            scanf("%d", &x);
            set(rs, i, x, x);
        }
        for (int i = 1; i <= m; ++i) {
            int x;
            scanf("%d", &x);
            set(n + i, rt, x, x);
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                lo[i][j] = 0, hi[i][j] = INF;
        scanf("%d", &u);
        bool f = true;
        while (u--) {
            char op;
            int x, y, z, x1, x2, y1, y2;
            scanf("%d%d %c%d", &x, &y, &op, &z);
            if (!f)
                continue;
            if (!x)
                x1 = 1, x2 = n;
            else
                x1 = x2 = x;
            if (!y)
                y1 = 1, y2 = m;
            else
                y1 = y2 = y;
            for (int i = x1; i <= x2; ++i)
                for (int j = y1; j <= y2; ++j)
                    if (op == '=') {
                        if (z < lo[i][j] || z > hi[i][j])
                            f = false;
                        lo[i][j] = hi[i][j] = z;
                    }
                    else if (op == '<') {
                        if (z <= lo[i][j])
                            f = false;
                        if (z - 1 < hi[i][j])
                            hi[i][j] = z - 1;
                    }
                    else {
                        if (z >= hi[i][j])
                            f = false;
                        if (z + 1 > lo[i][j])
                            lo[i][j] = z + 1;
                    }
        }
        if (!f) {
            puts("IMPOSSIBLE");
            continue;
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                set(i, n + j, lo[i][j], hi[i][j]);
        add(rt, rs, INF);
        int flow = 0;
        while (bfs()) {
            memcpy(g, h, sizeof h);
            flow += dfs(s, INF);
        }
        if (flow != sum) {
            puts("IMPOSSIBLE");
            continue;
        }
        for (int i = 1; i <= m; ++i)
            for (int k = h[n + i]; ~k; k = nxt[k])
                if (p[k] <= n)
                    lo[p[k]][i] += c[k];
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < m; ++j)
                printf("%d ", lo[i][j]);
            printf("%d\n", lo[i][m]);
        }
        if (cs)
            puts("");
    }
    return 0;
}
