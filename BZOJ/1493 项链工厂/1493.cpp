#include <algorithm>
#include <cstdio>

using namespace std;

#define lc x << 1
#define rc (lc) + 1

const int MAXN = 2222222;

struct data {
    int c, l, r;

    inline data(int _c = 0, int _l = 0, int _r = 0) : c(_c), l(_l), r(_r) {}

    inline data operator + (const data &x) {
        return !c ? x : !x.c ? *this : data(c + x.c - (r == x.l), l, x.r);
    }
} d[MAXN];

char op[3];
int e[MAXN];

inline void update(int x) {
    d[x] = d[lc] + d[rc];
}

inline void doc(int x, int v) {
    d[x] = data(1, e[x] = v, v);
}

inline void push(int x) {
    if (e[x]) {
        doc(lc, e[x]);
        doc(rc, e[x]);
        e[x] = 0;
    }
}

void build(int x, int f, int t) {
    if (f == t) {
        int v;
        scanf("%d", &v);
        d[x] = data(1, v, v);
        return;
    }
    int mid = f + t >> 1;
    build(lc, f, mid);
    build(rc, mid + 1, t);
    update(x);
}

void modify(int x, int f, int t, int q, int v) {
    if (f == t) {
        d[x] = data(1, v, v);
        return;
    }
    push(x);
    int mid = f + t >> 1;
    if (q <= mid)
        modify(lc, f, mid, q, v);
    else
        modify(rc, mid + 1, t, q, v);
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

int main() {
    int n, q, h = 0, p = 1;
    scanf("%d%*d", &n);
    build(1, 0, n - 1);
    scanf("%d", &q);
    while (q--) {
        int i, j, x, y;
        scanf("%s", op);
        if (op[0] == 'R') {
            scanf("%d", &x);
            h = (h - x * p + n) % n;
        }
        else if (op[0] == 'F')
            p = -p;
        else if (op[0] == 'S') {
            scanf("%d%d", &i, &j);
            i = (h + (i - 1) * p + n) % n;
            j = (h + (j - 1) * p + n) % n;
            x = query(1, 0, n - 1, i, i).l;
            y = query(1, 0, n - 1, j, j).l;
            modify(1, 0, n - 1, i, y);
            modify(1, 0, n - 1, j, x);
        }
        else if (op[0] == 'P') {
            scanf("%d%d%d", &i, &j, &x);
            i = (h + (i - 1) * p + n) % n;
            j = (h + (j - 1) * p + n) % n;
            if (p < 0)
                swap(i, j);
            if (j < i) {
                cover(1, 0, n - 1, i, n - 1, x);
                cover(1, 0, n - 1, 0, j, x);
            }
            else
                cover(1, 0, n - 1, i, j, x);
        }
        else if (op[1] == 'S') {
            scanf("%d%d", &i, &j);
            i = (h + (i - 1) * p + n) % n;
            j = (h + (j - 1) * p + n) % n;
            if (p < 0)
                swap(i, j);
            printf("%d\n", max(j < i ? (query(1, 0, n - 1, i, n - 1) + query(1, 0, n - 1, 0, j)).c : query(1, 0, n - 1, i, j).c, 1));
        }
        else
            printf("%d\n", max(d[1].c - (d[1].l == d[1].r), 1));
    }
    return 0;
}
