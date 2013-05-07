#include <cmath>
#include <cstdio>
#include <cstring>

typedef long long LL;

const int MAXN = 55555, MOD = 999983;

int tot, h[MOD], p[MAXN], r[MAXN], nxt[MAXN];

inline int find(int x) {
    for (int k = h[x % MOD]; k; k = nxt[k])
        if (p[k] == x)
            return k;
    return -1;
}

inline void insert(int x, int y) {
    if (!~find(x)) {
        int v = x % MOD;
        p[++tot] = x;
        r[tot] = y;
        nxt[tot] = h[v];
        h[v] = tot;
    }
}

void exgcd(int a, int b, int c, LL &x, LL &y) {
    if (!b) {
        x = c / a, y = 0;
        return;
    }
    LL tx, ty;
    exgcd(b, a % b, c, tx, ty);
    x = ty, y = tx - a / b * ty;
}

inline int calc(int a, int b, int c) {
    LL t = 1 % c, e = t;
    int m = int(ceil(sqrt(c)));
    for (int i = 0; i < m; ++i, e = e * a % c)
        insert(e, i);
    for (int i = 0; i <= m; ++i, t = t * e % c) {
        LL x, y;
        exgcd(t, c, b, x, y);
        int k = find((x % c + c) % c);
        if (~k)
            return i * m + r[k];
    }
    return -1;
}

int main() {
    int p, b, n;
    while (scanf("%d%d%d", &p, &b, &n) != EOF) {
        memset(h, tot = 0, sizeof h);
        int t = calc(b, n, p);
        if (~t)
            printf("%d\n", t);
        else
            puts("no solution");
    }
    return 0;
}
