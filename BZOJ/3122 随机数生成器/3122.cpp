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

inline int calc1(int a, int b, int c) {
    int d = abs(__gcd(a, b));
    if (c % d)
        return -2;
    LL x, y;
    exgcd(a, b, c, x, y);
    b /= d;
    return (x % b + b) % b;
}

inline int calc2(int a, int b, int c, int d) {
    if (!d && !b)
        return 0;
    memset(h, tot = 0, sizeof h);
    LL t = 1 % c, e = t;
    int m = int(ceil(sqrt(c)));
    for (int i = 0; i < m; ++i, e = e * a % c)
        insert(e, i);
    for (int i = 0; i <= m; ++i, t = t * e % c) {
        int q = calc1(d * t % c, c, b);
        if (q != -2) {
            int k = find(q);
            if (~k)
                return i * m + r[k];
        }
    }
    return -2;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int p, a, b, x1, xn;
        scanf("%d%d%d%d%d", &p, &a, &b, &x1, &xn);
        if (a == 1)
            printf("%d\n", calc1(b, p, xn - x1) + 1);
        else
            printf("%d\n", calc2(a, (LL(a - 1) * xn + b) % p, p, (LL(a - 1) * x1 + b) % p) + 1);
    }
    return 0;
}
