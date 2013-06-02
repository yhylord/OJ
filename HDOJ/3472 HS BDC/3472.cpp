#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXC = 33, MAXN = 2222, INF = 1000000000;

bool ex[MAXC];
char a[MAXC];
int tot, n, s, t, d[MAXC], q[MAXC], f[MAXC], dg[MAXC], g[MAXC], h[MAXC], p[MAXN << 1], c[MAXN << 1], nxt[MAXN << 1];

struct edge {
    int x, y, z;
} e[MAXN];

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

inline bool check() {
    bool b = false;
    for (int i = 0; i < 26; ++i)
        if (f[i] == i && ex[i]) {
            if (b)
                return false;
            b = true;
        }
    return true;
}

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
    int ret = 0, flow;
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

inline bool dinic(int x, int y) {
    int flow = tot = 0, sum = 0;
    s = 26, t = 27;
    memset(h, -1, sizeof h);
    ++dg[x];
    --dg[y];
    for (int i = 0; i < 26; ++i)
        if (dg[i] > 0) {
            add(s, i, dg[i] >> 1);
            sum += dg[i] >> 1;
        }
        else if (dg[i] < 0)
            add(i, t, -dg[i] >> 1);
    for (int i = 0; i < n; ++i)
        if (e[i].z)
            add(e[i].y, e[i].x, 1);
    while (bfs()) {
        memcpy(g, h, sizeof h);
        flow += dfs(s, INF);
    }
    --dg[x];
    ++dg[y];
    return flow == sum;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int cs = 1; cs <= t; ++cs) {
        printf("Case %d: ", cs);
        scanf("%d", &n);
        for (int i = 0; i < 26; ++i) {
            dg[f[i] = i] = 0;
            ex[i] = false;
        }
        for (int i = 0; i < n; ++i) {
            scanf("%s%d", a, &e[i].z);
            int x = a[0] - 'a', y = a[strlen(a) - 1] - 'a';
            e[i].x = x, e[i].y = y;
            ex[x] = ex[y] = true;
            --dg[x], ++dg[y];
            if ((x = find(x)) != (y = find(y)))
                f[x] = y;
        }
        int cnt = 0, x = 1, y = 1;
        for (int i = 0; i < 26; ++i)
            if (dg[i] & 1)
                if (++cnt == 1)
                    x = i;
                else
                    y = i;
        if (!check() || cnt && cnt != 2) {
            puts("Poor boy!");
            continue;
        }
        puts(dinic(x, y) || dinic(y, x) ? "Well done!" : "Poor boy!");
    }
    return 0;
}
