#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 111111;

struct bit {
    int s[MAXN];

    inline int getsum(int x) {
        int ret = 0;
        for (; x; x -= x & -x)
            ret += s[x];
        return ret;
    }

    inline void update(int x, int v) {
        for (; x < MAXN; x += x & -x)
            s[x] += v;
    }
} a, b;

int edgecnt, h[MAXN], p[MAXN << 1], nxt[MAXN << 1], c[MAXN], belong[MAXN], no[MAXN], size[MAXN];

inline void addedge(int u, int v) {
    p[++edgecnt] = v;
    nxt[edgecnt] = h[u];
    h[u] = edgecnt;
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    c[1] = MAXN;
    int nodecnt = 0, listcnt = 0;
    for (int k = h[1]; k; k = nxt[k])
        if (!c[p[k]]) {
            ++listcnt;
            for (int t = k; t; )
                if (!c[p[t]]) {
                    c[p[t]] = ++nodecnt;
                    belong[p[t]] = listcnt;
                    no[p[t]] = ++size[listcnt];
                    t = h[p[t]];
                }
                else
                    t = nxt[t];
        }
    int root = 0;
    while (q--) {
        int op, u, x, d;
        scanf("%d%d", &op, &u);
        if (op)
            printf("%d\n", u == 1 ? root : a.getsum(c[u]) + b.getsum(no[u]));
        else {
            scanf("%d%d", &x, &d);
            if (u == 1) {
                root += x;
                b.update(1, x);
                b.update(d + 1, -x);
            }
            else {
                if (d > no[u] - 1) {
                    root += x;
                    b.update(1, x);
                    b.update(d - no[u] + 1, -x);
                    a.update(c[u] - no[u] + 1, -x);
                    a.update(min(c[u] + size[belong[u]] - no[u] + 1, c[u] - no[u] + 1 + d - no[u]), x);
                }
                a.update(c[u] - min(no[u] - 1, d), x);
                a.update(c[u] + min(d, size[belong[u]] - no[u]) + 1, -x);
            }
        }
    }
    return 0;
}
