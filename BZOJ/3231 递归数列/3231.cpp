#include <cstdio>
#include <cstring>

typedef long long LL;

const int MAXK = 17;

int k, p, s[MAXK], u[MAXK], v[MAXK][MAXK], a[MAXK], b[MAXK][MAXK], c[MAXK][MAXK];

inline int calc(LL n) {
    if (n <= k)
        return s[n];
    memcpy(a, u, sizeof u);
    memcpy(b, v, sizeof v);
    for (n -= k; n; n >>= 1) {
        if (n & 1) {
            memset(c[0], 0, sizeof c[0]);
            for (int i = 0; i <= k; ++i)
                for (int j = 0; j <= k; ++j)
                    (c[0][i] += LL(b[i][j]) * a[j] % p) %= p;
            memcpy(a, c[0], sizeof c[0]);
        }
        memset(c, 0, sizeof c);
        for (int i = 0; i <= k; ++i)
            for (int j = 0; j <= k; ++j)
                for (int l = 0; l <= k; ++l)
                    (c[i][j] += LL(b[i][l]) * b[l][j] % p) %= p;
        memcpy(b, c, sizeof c);
    }
    return (a[0] + a[k]) % p;
}

int main() {
    scanf("%d", &k);
    for (int i = 1; i <= k; ++i)
        scanf("%d", &u[k - i]);
    for (int i = 0; i < k; ++i)
        scanf("%d", &v[0][i]);
    for (int i = 1; i < k; ++i)
        v[i][i - 1] = 1;
    v[k][0] = v[k][k] = 1;
    LL m, n;
    scanf("%lld%lld%d", &m, &n, &p);
    for (int i = 1; i <= k; ++i)
        s[i] = (s[i - 1] + u[k - i]) % p;
    u[k] = s[k - 1];
    printf("%d\n", (calc(n) - calc(m - 1) + p) % p);
    return 0;
}
