#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 111111, MAXT = 1777777;

int k, tot, a[MAXN], b[MAXN], c[MAXN], root[MAXN], g[MAXN], s[MAXT], l[MAXT], r[MAXT];

void insert(int x, int &y, int f, int t, int v) {
    s[y = ++tot] = s[x] + 1;
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

bool query(int x, int y, int f, int t, int v) {
    if (s[y] - s[x] == 0)
        return false;
    if (f == t)
        return true;
    int mid = f + t >> 1;
    return v <= mid ? query(l[x], l[y], f, mid, v) : query(r[x], r[y], mid + 1, t, v);
}

inline bool cmp1(int x, int y) {
    for (int i = 0; i < k; ++i) {
        if (a[x + i] < a[y + i])
            return true;
        if (a[x + i] > a[y + i])
            return false;
    }
    return false;
}

inline int cmp2(int x) {
    for (int i = 0; i < k; ++i) {
        if (a[x + i] < b[i])
            return -1;
        if (a[x + i] > b[i])
            return 1;
    }
    return 0;
}

inline bool dif(int x, int y) {
    for (int i = 0; i < k; ++i)
        if (a[x + i] != a[y + i])
            return true;
    return false;
}

int main() {
    int n, m, idx = 1;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[c[i] = i]);
    sort(c + 1, c + n + 1, cmp1);
    g[c[1]] = 1;
    for (int i = 2; i <= n; ++i)
        g[c[i]] = idx += dif(c[i - 1], c[i]);
    for (int i = 1; i + k - 1 <= n; ++i)
        insert(root[i - 1], root[i], 1, idx, g[i]);
    while (m--) {
        int l, r, x = 0;
        scanf("%d%d", &l, &r);
        for (int i = 0; i < k; ++i)
            scanf("%d", &b[i]);
        int f = 0, t = n + 1;
        while (f + 1 < t) {
            int mid = f + t >> 1;
            if (cmp2(c[mid]) <= 0)
                f = mid;
            else
                t = mid;
        }
        puts(!cmp2(c[f]) && query(root[l - 1], root[r - k + 1], 1, idx, g[c[f]]) ? "No" : "Yes");
    }
    return 0;
}
