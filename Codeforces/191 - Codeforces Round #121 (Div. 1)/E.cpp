#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

const int MAXN = 111111, MAXT = 1811111;

int root[MAXN], l[MAXT], r[MAXT], d[MAXT];
LL tot, a[MAXN], b[MAXN];

void insert(int x, int &y, int f, int t, int v) {
    d[y = ++tot] = d[x] + 1;
    if (f == t)
        return;
    int mid = f + t >> 1;
    if (v <= mid) {
        r[y] = r[x];
        insert(l[x], l[y], f, mid, v);
    }
    else {
        l[y] = l[x];
        insert(r[x], r[y], mid + 1, t, v);
    }
}

int query(int x, int f, int t, int v) {
    if (v < 0)
        return 0;
    if (f == t)
        return d[x];
    int mid = f + t >> 1;
    if (v <= mid)
        return query(l[x], f, mid, v);
    return d[l[x]] + query(r[x], mid + 1, t, v);
}

int main() {
    int n;
    LL k;
    scanf("%d%I64d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%I64d", &a[i]);
        b[i] = a[i] += a[i - 1];
    }
    sort(b, b + n + 1);
    int m = unique(b, b + n + 1) - b;
    for (int i = 1; i <= n + 1; ++i)
        insert(root[i - 1], root[i], 0, m - 1, lower_bound(b, b + m, a[i - 1]) - b);
    LL lo = -100000000000000LL, hi = -lo;
    while (lo + 1 < hi) {
        LL mid = lo + hi >> 1, cnt = 0;
        for (int i = 1; i <= n; ++i)
            cnt += query(root[i], 0, m - 1, upper_bound(b, b + m, a[i] - mid) - b - 1);
        if (cnt >= k)
            lo = mid;
        else
            hi = mid;
    }
    printf("%I64d\n", lo);
    return 0;
}
