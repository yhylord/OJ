#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define lc x << 1
#define rc (lc) + 1

const int MAXN = 55555, MAXT = MAXN * 33, INF = 100000001;

int tot, s[MAXT], l[MAXT], r[MAXT], p[MAXT], k[MAXT], root[MAXN << 2], a[MAXN];

inline void update(int x) {
    s[x] = s[l[x]] + s[r[x]] + 1;
}

inline void zig(int &x) {
    int y = l[x];
    l[x] = r[y], r[y] = x;
    update(x), x = y;
}

inline void zag(int &x) {
    int y = r[x];
    r[x] = l[y], l[y] = x;
    update(x), x = y;
}

void insert(int &x, int v) {
    if (!x)
        k[x = ++tot] = v, p[x] = rand();
    else if (v < k[x]) {
        insert(l[x], v);
        if (p[l[x]] > p[x])
            zig(x);
    }
    else {
        insert(r[x], v);
        if (p[r[x]] > p[x])
            zag(x);
    }
    update(x);
}

void erase(int &x, int v) {
    if (v == k[x]) {
        if (!l[x] || !r[x]) {
            x = l[x] + r[x];
            return;
        }
        else if (p[l[x]] > p[r[x]])
            zig(x), erase(r[x], v);
        else
            zag(x), erase(l[x], v);
    }
    else
        erase(v < k[x] ? l[x] : r[x], v);
    update(x);
}

int rank(int x, int v) {
    return !x ? 0 : v <= k[x] ? rank(l[x], v) : s[l[x]] + 1 + rank(r[x], v);
}

int pred(int x, int v) {
    int t;
    return !x ? -1 : v <= k[x] ? pred(l[x], v) : ~(t = pred(r[x], v)) ? t : k[x];
}

int succ(int x, int v) {
    int t;
    return !x ? INF : v >= k[x] ? succ(r[x], v) : (t = succ(l[x], v)) < INF ? t : k[x];
}

void build(int x, int f, int t) {
    for (int i = f; i <= t; ++i)
        insert(root[x], a[i]);
    if (f == t)
        return;
    int mid = f + t >> 1;
    build(lc, f, mid);
    build(rc, mid + 1, t);
}

void modify(int x, int f, int t, int p, int v) {
    erase(root[x], a[p]);
    insert(root[x], v);
    if (f == t)
        return;
    int mid = f + t >> 1;
    if (p <= mid)
        modify(lc, f, mid, p, v);
    else
        modify(rc, mid + 1, t, p, v);
}

int getrank(int x, int f, int t, int qf, int qt, int v) {
    if (qf <= f && t <= qt)
        return rank(root[x], v);
    int mid = f + t >> 1, ret = 0;
    if (qf <= mid)
        ret += getrank(lc, f, mid, qf, qt, v);
    if (qt > mid)
        ret += getrank(rc, mid + 1, t, qf, qt, v);
    return ret;
}

int getpred(int x, int f, int t, int qf, int qt, int v) {
    if (qf <= f && t <= qt)
        return pred(root[x], v);
    int mid = f + t >> 1, ret = 0;
    if (qf <= mid)
        ret = max(ret, getpred(lc, f, mid, qf, qt, v));
    if (qt > mid)
        ret = max(ret, getpred(rc, mid + 1, t, qf, qt, v));
    return ret;
}

int getsucc(int x, int f, int t, int qf, int qt, int v) {
    if (qf <= f && t <= qt)
        return succ(root[x], v);
    int mid = f + t >> 1, ret = INF;
    if (qf <= mid)
        ret = min(ret, getsucc(lc, f, mid, qf, qt, v));
    if (qt > mid)
        ret = min(ret, getsucc(rc, mid + 1, t, qf, qt, v));
    return ret;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    build(1, 1, n);
    while (m--) {
        int op, x, y, z;
        scanf("%d%d%d", &op, &x, &y);
        if (op != 3)
            scanf("%d", &z);
        if (op == 1)
            printf("%d\n", getrank(1, 1, n, x, y, z) + 1);
        else if (op == 2) {
            int f = -1, t = INF;
            while (f + 1 < t) {
                int mid = f + t >> 1;
                if (getrank(1, 1, n, x, y, mid) < z)
                    f = mid;
                else
                    t = mid;
            }
            printf("%d\n", f);
        }
        else if (op == 3) {
            modify(1, 1, n, x, y);
            a[x] = y;
        }
        else if (op == 4)
            printf("%d\n", getpred(1, 1, n, x, y, z));
        else
            printf("%d\n", getsucc(1, 1, n, x, y, z));
    }
    return 0;
}
