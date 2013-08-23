#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 111111;

int tot, a[MAXN], d[MAXN], q[MAXN], f[MAXN], h[MAXN], p[MAXN], nxt[MAXN];
unsigned s[MAXN];

inline void bfs() {
    int r = 0;
    d[q[0] = 1] = 1;
    for (int l = 0; l <= r; ++l)
        for (int k = h[q[l]]; k; k = nxt[k])
            d[q[++r] = p[k]] = d[q[l]] + 1;
}

inline bool check(int x, int y) {
    if (d[x] > d[y])
        swap(x, y);
    for (s[0] = 0; s[0] < 50 && d[x] < d[y] && (s[++s[0]] = a[y]); y = f[y]);
    for (; s[0] < 50 && x != y && (s[++s[0]] = a[x]) && (s[++s[0]] = a[y]); x = f[x], y = f[y]);
    s[++s[0]] = a[x];
    if (s[0] >= 50)
        return true;
    if (s[0] < 3)
        return false;
    sort(s + 1, s + s[0] + 1);
    for (int i = 1; i + 2 <= s[0]; ++i)
        if (s[i] + s[i + 1] > s[i + 2])
            return true;
    return false;
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        nxt[i] = h[x];
        h[f[p[i] = y] = x] = i;
    }
    bfs();
    while (q--) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        if (op)
            a[x] = y;
        else
            puts(check(x, y) ? "Y" : "N");
    }
    return 0;
}
