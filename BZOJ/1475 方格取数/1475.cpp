#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
const int MAXN = 1111, MAXM = 5555, INF = 1000000000;

int s, t, n, tot, d[MAXN], q[MAXN], g[MAXN], h[MAXN], p[MAXM], c[MAXM], nxt[MAXM];

inline int no(int i, int j) {
    return (i - 1) * n + j;
}

inline void addedge(int x, int y, int z) {
    p[tot] = y;
    c[tot] = z;
    nxt[tot] = h[x];
    h[x] = tot++;
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
        if (c[k] && d[p[k]] == d[x] + 1 && (flow = dfs(p[k], min(ext, c[k])))) {
            c[k] -= flow;
            c[k ^ 1] += flow;
            return flow;
        }
    return 0;
}

int main() {
    int ans = 0;
    scanf("%d", &n);
    t = n * n + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            int x;
            scanf("%d", &x);
            ans += x;
            if ((i + j) & 1) {
                addedge(s, no(i, j), x);
                addedge(no(i, j), s, 0);
                for (int k = 0; k < 4; ++k) {
                    int ti = i + di[k], tj = j + dj[k];
                    if (ti && ti <= n && tj && tj <= n) {
                        addedge(no(i, j), no(ti, tj), INF);
                        addedge(no(ti, tj), no(i, j), 0);
                    }
                }
            }
            else {
                addedge(no(i, j), t, x);
                addedge(t, no(i, j), 0);
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
