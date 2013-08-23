#include <algorithm>
#include <cstdio>

using namespace std;

#define lc x << 1
#define rc (lc) + 1

const int MAXN = 111111;

int tot, n, a[MAXN], b[MAXN], c[MAXN << 2], h[MAXN], p[MAXN << 1], nxt[MAXN << 1],
    hd[MAXN], dep[MAXN], idx[MAXN], pre[MAXN], suc[MAXN], sz[MAXN], q[MAXN];

struct data {
    int l, r, s;

    inline data(int _l = -1, int _r = -1, int _s = 0): l(_l), r(_r), s(_s) {}

    inline data operator +(const data &t) {
        return !~l ? t : !~t.l ? *this : data(l, t.r, s + t.s - (r == t.l));
    }
} d[MAXN << 2];

inline void addedge(int x, int y) {
    p[++tot] = y, nxt[tot] = h[x], h[x] = tot;
}

inline void doc(int x, int v) {
    d[x] = data(c[x] = v, v, 1);
}

inline void push(int x) {
    if (~c[x]) {
        doc(lc, c[x]);
        doc(rc, c[x]);
        c[x] = -1;
    }
}

void build(int x, int f, int t) {
    c[x] = -1;
    if (f == t) {
        d[x] = data(b[f], b[f], 1);
        return;
    }
    int mid = f + t >> 1;
    build(lc, f, mid);
    build(rc, mid + 1, t);
    d[x] = d[lc] + d[rc];
}

void cover(int x, int f, int t, int qf, int qt, int v) {
    if (qf <= f && t <= qt) {
        doc(x, v);
        return;
    }
    push(x);
    int mid = f + t >> 1;
    if (qf <= mid)
        cover(lc, f, mid, qf, qt, v);
    if (qt > mid)
        cover(rc, mid + 1, t, qf, qt, v);
    d[x] = d[lc] + d[rc];
}

data query(int x, int f, int t, int qf, int qt) {
    if (qf <= f && t <= qt)
        return d[x];
    push(x);
    data l, r;
    int mid = f + t >> 1;
    if (qf <= mid)
        l = query(lc, f, mid, qf, qt);
    if (qt > mid)
        r = query(rc, mid + 1, t, qf, qt);
    return l + r;
}

inline void put(int x, int y, int v) {
    while (hd[x] != hd[y])
        if (dep[hd[x]] > dep[hd[y]]) {
            cover(1, 1, n, idx[hd[x]], idx[x], v);
            x = pre[hd[x]];
        }
        else {
            cover(1, 1, n, idx[hd[y]], idx[y], v);
            y = pre[hd[y]];
        }
    if (idx[x] > idx[y])
        cover(1, 1, n, idx[y], idx[x], v);
    else
        cover(1, 1, n, idx[x], idx[y], v);
}

inline int get(int x, int y) {
    data l, r;
    while (hd[x] != hd[y])
        if (dep[hd[x]] > dep[hd[y]]) {
            l = query(1, 1, n, idx[hd[x]], idx[x]) + l;
            x = pre[hd[x]];
        }
        else {
            r = query(1, 1, n, idx[hd[y]], idx[y]) + r;
            y = pre[hd[y]];
        }
    if (idx[x] > idx[y])
        l = query(1, 1, n, idx[y], idx[x]) + l;
    else
        r = query(1, 1, n, idx[x], idx[y]) + r;
    swap(l.l, l.r);
    return (l + r).s;
}

int main() {
    int m, r = 0, cnt = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y);
        addedge(y, x);
    }
    q[0] = dep[1] = 1;
    for (int l = 0; l <= r; ++l)
        for (int k = h[q[l]]; k; k = nxt[k])
            if (!dep[p[k]])
                dep[q[++r] = p[k]] = dep[pre[p[k]] = q[l]] + 1;
    for (int i = r; i >= 0; --i) {
        sz[pre[q[i]]] += ++sz[q[i]];
        if (sz[q[i]] > sz[suc[pre[q[i]]]])
            suc[pre[q[i]]] = q[i];
    }
    for (int i = 0; i <= r; ++i)
        if (!hd[q[i]])
            for (int k = q[i]; k; k = suc[k]) {
                hd[k] = q[i];
                b[idx[k] = ++cnt] = a[k];
            }
    build(1, 1, n);
    while (m--) {
        char op;
        int x, y, z;
        scanf(" %c%d%d", &op, &x, &y);
        if (op == 'C') {
            scanf("%d", &z);
            put(x, y, z);
        }
        else
            printf("%d\n", get(x, y));
    }
    return 0;
}
