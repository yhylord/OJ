#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long LL;

const int MAXN = 33333, MOD = 999983;

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
    if (b >= c)
        return -1;
    int q = 0;
    LL t = 1 % c, d = t, e = t;
    for (int i = 0; i <= 100; ++i, t = t * a % c)
        if (t == b)
            return i;
    for (; (t = __gcd(a, c)) != 1; ++q, b /= t, c /= t, d = d * a / t % c)
        if (b % t)
            return -1;
    int m = int(ceil(sqrt(c)));
    for (int i = 0; i < m; ++i, e = e * a % c)
        insert(e, i);
    t = 1 % c;
    for (int i = 0; i <= m; ++i, t = t * e % c) {
        LL x, y;
        exgcd(d * t % c, c, b, x, y);
        int k = find((x % c + c) % c);
        if (~k)
            return i * m + r[k] + q;
    }
    return -1;
}

int main() {
    int k, p, n;
    while (scanf("%d%d%d", &k, &p, &n) != EOF) {
        memset(h, tot = 0, sizeof h);
        int t = calc(k, n, p);
        if (~t)
            printf("%d\n", t);
        else
            puts("Orz,I can¡¯t find D!");
    }
    return 0;
}
