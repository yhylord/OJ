#include <cstdio>

typedef long double LD;
typedef long long LL;

const int MAXN = 1111111;

int x[MAXN], p[MAXN], c[MAXN], q[MAXN];
LL s[MAXN], d[MAXN], f[MAXN], g[MAXN];

inline LL calc(int i, int j) {
    return g[j] - s[j] * x[i];
}

int main() {
    int n, l = 0, r = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &x[i], &p[i], &c[i]);
        s[i] = s[i - 1] + p[i];
    }
    for (int i = n; i; --i)
        d[i] = d[i + 1] + LL(x[n] - x[i]) * p[i];
    g[0] = d[1];
    for (int i = 1; i <= n; ++i) {
        for (; l < r && calc(i, q[l + 1]) < calc(i, q[l]); ++l);
        f[i] = calc(i, q[l]) - d[i + 1] - s[i] * (x[n] - x[i]) + c[i];
        g[i] = f[i] + d[i + 1] + s[i] * x[n];
        for (; r && LD(g[q[r]] - g[q[r - 1]]) / (s[q[r]] - s[q[r - 1]]) >= LD(g[i] - g[q[r]]) / (s[i] - s[q[r]]); --r);
        q[++r] = i;
        if (l > r)
            l = r;
    }
    printf("%lld\n", f[n]);
    return 0;
}
