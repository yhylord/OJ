#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 111111, MAXT = 1811111;

int tot, a[MAXN], b[MAXN], d[MAXT], l[MAXT], r[MAXT], root[MAXT];

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

int query(int x, int y, int f, int t, int v) {
    if (f == t)
        return f;
    int mid = f + t >> 1;
    if (v <= d[l[y]] - d[l[x]])
        return query(l[x], l[y], f, mid, v);
    return query(r[x], r[y], mid + 1, t, v - d[l[y]] + d[l[x]]);
}

int main() {
    int n, m, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    m = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; ++i)
        insert(root[i - 1], root[i], 1, m, lower_bound(b + 1, b + m + 1, a[i]) - b);
    while (q--) {
        int i, j, k;
        scanf("%d%d%d", &i, &j, &k);
        printf("%d\n", b[query(root[i - 1], root[j], 1, m, k)]);
    }
    return 0;
}
