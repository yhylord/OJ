#include <algorithm>
#include <cstdio>

using namespace std;

#define lc x << 1
#define rc (lc) + 1

const int MAXN = 222222;

int f[MAXN], s[MAXN], d[MAXN << 2];

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

void insert(int x, int f, int t, int p, int v) {
    d[x] += v;
    if (f == t)
        return;
    int mid = f + t >> 1;
    if (p <= mid)
        insert(lc, f, mid, p, v);
    else
        insert(rc, mid + 1, t, p, v);
}

int query(int x, int f, int t, int v) {
    if (f == t)
        return f;
    int mid = f + t >> 1, cur = d[rc];
    if (v <= cur)
        return query(rc, mid + 1, t, v);
    return query(lc, f, mid, v - cur);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
        s[i] = 1;
    }
    insert(1, 1, n, 1, 1);
    while (m--) {
        int c, i, j, k;
        scanf("%d", &c);
        if (!c) {
            scanf("%d%d", &i, &j);
            int x = find(i), y = find(j);
            if (x != y) {
                insert(1, 1, n, s[x], -1);
                insert(1, 1, n, s[y], -1);
                if (s[x] < s[y])
                    swap(x, y);
                f[y] = x;
                insert(1, 1, n, s[x] += s[y], 1);
            }
        }
        else {
            scanf("%d", &k);
            printf("%d\n", query(1, 1, n, k));
        }
    }
    return 0;
}
