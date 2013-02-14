#include <algorithm>
#include <cstdio>

using namespace std;

#define l x << 1
#define r (l) + 1

typedef long long LL;

const int MAXN = 444444;

LL d[MAXN], e[MAXN];

inline void push(int x) {
    if (e[x]) {
        d[l] = d[r] = e[l] = e[r] = e[x];
        e[x] = 0;
    }
}

inline void update(int x) {
    d[x] = max(d[l], d[r]);
}

void build(int x, int f, int t) {
    if (f == t) {
        scanf("%I64d", &d[x]);
        return;
    }
    int mid = f + t >> 1;
    build(l, f, mid);
    build(r, mid + 1, t);
    update(x);
}

LL query(int x, int f, int t, int qf, int qt) {
    if (qf <= f && t <= qt)
        return d[x];
    push(x);
    int mid = f + t >> 1;
    LL a = 0, b = 0;
    if (qf <= mid)
        a = query(l, f, mid, qf, qt);
    if (qt > mid)
        b = query(r, mid + 1, t, qf, qt);
    return max(a, b);
}

void set(int x, int f, int t, int qf, int qt, LL v) {
    if (qf <= f && t <= qt) {
        d[x] = e[x] = v;
        return;
    }
    push(x);
    int mid = f + t >> 1;
    if (qf <= mid)
        set(l, f, mid, qf, qt, v);
    if (qt > mid)
        set(r, mid + 1, t, qf, qt, v);
    update(x);
}

int main() {
    int n, m;
    scanf("%d", &n);
    build(1, 1, n);
    scanf("%d", &m);
    while (m--) {
        int w, h;
        scanf("%d%d", &w, &h);
        LL b = query(1, 1, n, 1, w);
        printf("%I64d\n", b);
        set(1, 1, n, 1, w, b + h);
    }
    return 0;
}
