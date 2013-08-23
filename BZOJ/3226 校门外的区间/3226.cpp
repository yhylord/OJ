#include <algorithm>
#include <cstdio>

using namespace std;

#define lc x << 1
#define rc (lc) + 1

const int MAXN = 66666, MAXT = 888888;

struct operation {
    char p, a, b;
    int x, y;
} a[MAXN];

int b[MAXN * 2], c[MAXN * 3], d[MAXT], e[MAXT];

inline void doc(int x, int v) {
    d[x] = v;
    e[x] = 0;
}

inline void dof(int x) {
    if (~d[x])
        d[x] ^= 1;
    else
        e[x] ^= 1;
}

inline void push(int x) {
    if (~d[x]) {
        doc(lc, d[x]);
        doc(rc, d[x]);
        d[x] = -1;
    }
    else if (e[x]) {
        dof(lc);
        dof(rc);
        e[x] = 0;
    }
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
}

void flip(int x, int f, int t, int qf, int qt) {
    if (qf <= f && t <= qt) {
        dof(x);
        return;
    }
    push(x);
    int mid = f + t >> 1;
    if (qf <= mid)
        flip(lc, f, mid, qf, qt);
    if (qt > mid)
        flip(rc, mid + 1, t, qf, qt);
}

void get(int x, int f, int t) {
    if (f == t) {
        c[f] = d[x];
        return;
    }
    push(x);
    int mid = f + t >> 1;
    get(lc, f, mid);
    get(rc, mid + 1, t);
}

int main() {
    int n = 0, m = 0;
    for (; scanf(" %c %c%d,%d%c", &a[n].p, &a[n].a, &a[n].x, &a[n].y, &a[n].b) != EOF; ++n) {
        if (a[n].x > a[n].y) {
            swap(a[n].x, a[n].y);
            swap(a[n].a, a[n].b);
        }
        b[m++] = a[n].x;
        b[m++] = a[n].y;
    }
    sort(b, b + m);
    int r = (m = unique(b, b + m) - b) * 3;
    for (int i = 0; i < n; ++i) {
        int x = (lower_bound(b, b + m, a[i].x) - b) * 3 + 1 + (a[i].a == '('),
            y = (lower_bound(b, b + m, a[i].y) - b) * 3 + 1 - (a[i].b == ')');
        if (a[i].p == 'U')
            cover(1, 0, r, x, y, 1);
        else if (a[i].p == 'I') {
            cover(1, 0, r, 0, x - 1, 0);
            cover(1, 0, r, y + 1, r, 0);
        }
        else if (a[i].p == 'D')
            cover(1, 0, r, x, y, 0);
        else if (a[i].p == 'C') {
            cover(1, 0, r, 0, x - 1, 0);
            cover(1, 0, r, y + 1, r, 0);
            flip(1, 0, r, x, y);
        }
        else
            flip(1, 0, r, x, y);
    }
    get(1, 0, r);
    bool got = false;
    for (int i = 1; i <= r; ++i)
        if (c[i]) {
            got = true;
            printf("%c%d,", i % 3 == 1 ? '[' : '(', b[i / 3]);
            int j = i;
            for (; c[j + 1]; ++j);
            printf("%d%c ", b[j / 3], j % 3 == 1 ? ']' : ')');
            i = j;
        }
    puts(got ? "" : "empty set");
    return 0;
}
