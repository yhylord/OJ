#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int di[] = {1, 0, 0}, dj[] = {0, 1, 0}, dk[] = {0, 0, 1};
const int MAXN = 66666, MAXM = 555555, INF = 1000000000;

int tot, s, t, n, d[MAXN], q[MAXN], g[MAXN], h[MAXN], p[MAXM], c[MAXM], nxt[MAXM];

inline void addedge(int x, int y, int z) {
    p[tot] = y;
    c[tot] = z;
    nxt[tot] = h[x];
    h[x] = tot++;
}

inline int no(int i, int j, int k) {
    return (i - 1) * n * n + (j - 1) * n + k;
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
    int flow;
    for (int &k = g[x]; ~k; k = nxt[k])
        if (c[k] && d[p[k]] == d[x] + 1 && (flow = dfs(p[k], min(c[k], ext)))) {
            c[k] -= flow;
            c[k ^ 1] += flow;
            return flow;
        }
    return 0;
}

int main() {
    int ans = 0;
    scanf("%d", &n);
    t = n * n * n + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 1; k <= n; ++k) {
                char x;
                scanf(" %c", &x);
                for (int l = 0; l < 3; ++l) {
                    int ti = i + di[l], tj = j + dj[l], tk = k + dk[l];
                    if (ti && ti <= n && tj && tj <= n && tk && tk <= n) {
                        ++ans;
                        addedge(no(i, j, k), no(ti, tj, tk), 1);
                        addedge(no(ti, tj, tk), no(i, j, k), 1);
                    }
                }
                if (x != '?')
                    if (((i + j + k) & 1) ^ (x == 'P')) {
                        addedge(s, no(i, j, k), INF);
                        addedge(no(i, j, k), s, 0);
                    }
                    else {
                        addedge(no(i, j, k), t, INF);
                        addedge(t, no(i, j, k), 0);
                    }
            }
    while (bfs()) {
        int flow;
        memcpy(g, h, sizeof h);
        while (flow = dfs(s, INF))
            ans -= flow;
    }
    printf("%d\n", ans);
    return 0;
}
