#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 50001, MAXT = 30000000;

struct query {
    int op, a, b, c;
} e[MAXN];

int n, m, tot, a[MAXN], v[MAXN], root[MAXN], u[MAXN], c[MAXT], d[MAXT], l[MAXT], r[MAXT];

void insert(int &x, int f, int t, int k, int v1, int v2) {
    if (!x)
        x = ++tot;
    c[x] += v1;
    d[x] += v2;
    if (f == t)
        return;
    int mid = f + t >> 1;
    if (k <= mid)
        insert(l[x], f, mid, k, v1, v2);
    else
        insert(r[x], mid + 1, t, k, v1, v2);
}

inline void update(int x, int k, int v1, int v2) {
    for (; x <= n; x += x & -x)
        insert(root[x], 1, m, k, v1, v2);
}

inline int getsum1(int x) {
    int ret = 0;
    for (; x; x -= x & -x)
        ret += c[r[u[x]]];
    return ret;
}

inline int getsum2(int x) {
    int ret = 0;
    for (; x; x -= x & -x)
        ret += d[r[u[x]]];
    return ret;
}

inline void init(int x) {
    for (; x; x -= x & -x) {
        u[x] = root[x];
        v[x] = 0;
    }
}

inline void turnl(int x, int cnt) {
    for (; x; x -= x & -x)
        if (v[x] != cnt) {
            u[x] = l[u[x]];
            v[x] = cnt;
        }
}

inline void turnr(int x, int cnt) {
    for (; x; x -= x & -x)
        if (v[x] != cnt) {
            u[x] = r[u[x]];
            v[x] = cnt;
        }
}

int main() {
    int q;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < q; ++i) {
        scanf("%d%d%d%d", &e[i].op, &e[i].a, &e[i].b, &e[i].c);
        if (e[i].op == 1)
            a[++m] = e[i].c;
    }
    sort(a + 1, a + m + 1);
    m = unique(a + 1, a + m + 1) - a - 1;
    for (int i = 0; i < q; ++i)
        if (e[i].op == 1) {
            update(e[i].a, lower_bound(a + 1, a + m + 1, e[i].c) - a, 1, e[i].a); 
            update(e[i].b + 1, lower_bound(a + 1, a + m + 1, e[i].c) - a, -1, -e[i].b - 1);
        }
        else {
            init(e[i].b);
            init(e[i].a - 1);
            int f = 1, t = m, cnt = 0;
            while (f < t) {
                ++cnt;
                int sb = (e[i].b + 1) * getsum1(e[i].b) - getsum2(e[i].b),
                    sa = e[i].a * getsum1(e[i].a - 1) - getsum2(e[i].a - 1),
                    cur = sb - sa, mid = f + t >> 1;
                if (e[i].c <= cur) {
                    f = mid + 1;
                    turnr(e[i].b, cnt);
                    turnr(e[i].a - 1, cnt);
                }
                else {
                    t = mid;
                    e[i].c -= cur;
                    turnl(e[i].b, cnt);
                    turnl(e[i].a - 1, cnt);
                }
            }
            printf("%d\n", a[f]);
        }
    return 0;
}
