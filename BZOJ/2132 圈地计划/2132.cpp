#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
const int MAXC = 111, MAXN = 11111, MAXM = 122222, INF = 1000000000;

int tot, s, t, a[MAXC][MAXC], id[MAXC][MAXC], d[MAXN], q[MAXN],
    g[MAXN], h[MAXN], p[MAXM], c[MAXM], nxt[MAXM];

inline void addedge(int x, int y, int z) {
    p[tot] = y, c[tot] = z, nxt[tot] = h[x], h[x] = tot++;
}

inline void add(int x, int y, int z) {
    addedge(x, y, z), addedge(y, x, 0);
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
            ret += flow, c[k] -= flow, c[k ^ 1] += flow;
            if (!(ext -= flow))
                return ret;
        }
    return ret;
}

int main() {
    int n, m, ans = 0;
    scanf("%d%d", &n, &m);
    s = 0, t = n * m + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            id[i][j] = (i - 1) * m + j;
            int x;
            scanf("%d", &x);
            ans += x;
            if ((i + j) & 1)
                add(s, id[i][j], x);
            else
                add(id[i][j], t, x);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            int x;
            scanf("%d", &x);
            ans += x;
            if ((i + j) & 1)
                add(id[i][j], t, x);
            else
                add(s, id[i][j], x);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 0; k < 4; ++k) {
                int x = i + dx[k], y = j + dy[k];
                if (x && x <= n && y && y <= m) {
                    ans += a[i][j];
                    add(id[i][j], id[x][y], a[i][j] + a[x][y]);
                }
            }
    while (bfs()) {
        memcpy(g, h, sizeof h);
        ans -= dfs(s, INF);
    }
    printf("%d\n", ans);
    return 0;
}
