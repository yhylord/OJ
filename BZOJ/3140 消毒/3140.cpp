#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 5555;

bool g[MAXN];
int a, b, c, cnt, tot, ans, idx, v[MAXN], h[MAXN], p[MAXN], nxt[MAXN], match[MAXN];

struct pos {
    int x, y, z;

    inline pos(int _x = 0, int _y = 0, int _z = 0) : x(_x), y(_y), z(_z) {}
} d[MAXN];

inline void addedge(int x, int y) {
    p[++tot] = y;
    nxt[tot] = h[x];
    h[x] = tot;
}

bool find(int x) {
    for (int k = h[x]; k; k = nxt[k])
        if (v[p[k]] != idx) {
            v[p[k]] = idx;
            if (!match[p[k]] || find(match[p[k]])) {
                match[p[k]] = x;
                return true;
            }
        }
    return false;
}

void dfs(int dep, int cur) {
    if (dep > a) {
        tot = 0;
        for (int i = 1; i <= b; ++i)
            h[i] = 0;
        for (int i = 1; i <= cnt; ++i)
            if (!g[d[i].x])
                addedge(d[i].y, d[i].z);
        for (int i = 1; i <= c; ++i)
            match[i] = 0;
        for (int i = 1; i <= b; ++i) {
            ++idx;
            if ((cur += find(i)) >= ans)
                return;
        }
        if (cur < ans)
            ans = cur;
        return;
    }
    g[dep] = true;
    dfs(dep + 1, cur + 1);
    g[dep] = false;
    dfs(dep + 1, cur);
}

int main() {
    int cs;
    scanf("%d", &cs);
    while (cs--) {
        scanf("%d%d%d", &a, &b, &c);
        cnt = 0;
        for (int i = 1; i <= a; ++i)
            for (int j = 1; j <= b; ++j)
                for (int k = 1; k <= c; ++k) {
                    int x;
                    scanf("%d", &x);
                    if (x)
                        if (a < b && a < c)
                            d[++cnt] = pos(i, j, k);
                        else if (b < a && b < c)
                            d[++cnt] = pos(j, i, k);
                        else
                            d[++cnt] = pos(k, j, i);
                }
        if (b < a && b < c)
            swap(a, b);
        if (c < a && c < b)
            swap(a, c);
        ans = a;
        dfs(1, 0);
        printf("%d\n", ans);
    }
    return 0;
}
