#include <algorithm>
#include <climits>
#include <cstdio>

using namespace std;

#define lc x << 1
#define rc (lc) + 1

const int MAXN = 444444;

int m[MAXN], d[MAXN], e[MAXN], hm[MAXN], hd[MAXN], he[MAXN];

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

inline void hdoa(int x, int v) {
    checkmax(hm[x], m[x] + v);
    if (e[x] > INT_MIN)
        checkmax(he[x], e[x] + v);
    else
        checkmax(hd[x], d[x] + v);
}

inline void hdoc(int x, int v) {
    checkmax(hm[x], v);
    checkmax(he[x], v);
}

inline void doa(int x, int v) {
    checkmax(hm[x], m[x] += v);
    if (e[x] > INT_MIN)
        checkmax(he[x], e[x] += v);
    else
        checkmax(hd[x], d[x] += v);
}

inline void doc(int x, int v) {
    checkmax(hm[x], m[x] = v);
    checkmax(he[x], e[x] = v);
    d[x] = 0;
}

inline void push(int x) {
    if (hd[x]) {
        hdoa(lc, hd[x]);
        hdoa(rc, hd[x]);
        hd[x] = 0;
    }
    if (he[x] > INT_MIN) {
        hdoc(lc, he[x]);
        hdoc(rc, he[x]);
        he[x] = INT_MIN;
    }
    if (d[x]) {
        doa(lc, d[x]);
        doa(rc, d[x]);
        d[x] = 0;
    }
    else if (e[x] > INT_MIN) {
        doc(lc, e[x]);
        doc(rc, e[x]);
        e[x] = INT_MIN;
    }
}

inline void update(int x) {
    m[x] = max(m[lc], m[rc]);
    checkmax(hm[x], max(hm[lc], hm[rc]));
}

void build(int x, int f, int t) {
    e[x] = he[x] = INT_MIN;
    if (f == t) {
        scanf("%d", &m[x]);
        hm[x] = m[x];
        return;
    }
    int mid = f + t >> 1;
    build(lc, f, mid);
    build(rc, mid + 1, t);
    hm[x] = INT_MIN;
    update(x);
}

void add(int x, int f, int t, int qf, int qt, int v) {
    if (qf <= f && t <= qt) {
        doa(x, v);
        return;
    }
    push(x);
    int mid = f + t >> 1;
    if (qf <= mid)
        add(lc, f, mid, qf, qt, v);
    if (qt > mid)
        add(rc, mid + 1, t, qf, qt, v);
    update(x);
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
    update(x);
}

int query(int x, int f, int t, int qf, int qt) {
    if (qf <= f && t <= qt)
        return m[x];
    push(x);
    int mid = f + t >> 1, l = INT_MIN, r = INT_MIN;
    if (qf <= mid)
        l = query(lc, f, mid, qf, qt);
    if (qt > mid)
        r = query(rc, mid + 1, t, qf, qt);
    return max(l, r);
}

int hquery(int x, int f, int t, int qf, int qt) {
    if (qf <= f && t <= qt)
        return hm[x];
    push(x);
    int mid = f + t >> 1, l = INT_MIN, r = INT_MIN;
    if (qf <= mid)
        l = hquery(lc, f, mid, qf, qt);
    if (qt > mid)
        r = hquery(rc, mid + 1, t, qf, qt);
    return max(l, r);
}

int main() {
    int n, q;
    scanf("%d", &n);
    build(1, 1, n);
    scanf("%d", &q);
    while (q--) {
        char op;
        int x, y, z;
        scanf(" %c%d%d", &op, &x, &y);
        if (op == 'Q')
            printf("%d\n", query(1, 1, n, x, y));
        else if (op == 'A')
            printf("%d\n", hquery(1, 1, n, x, y));
        else {
            scanf("%d", &z);
            if (op == 'P')
                add(1, 1, n, x, y, z);
            else
                cover(1, 1, n, x, y, z);
        }
    }
    return 0;
}
