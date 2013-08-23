#include <cstdio>

typedef long long LL;

const int MAXN = 1111111;

int a[MAXN], q[MAXN];
LL f[MAXN], g[MAXN];

inline LL calc(int i, int j) {
    return g[j] - LL(i) * j;
}

int main() {
    int n, l = 0, r = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        for (; l < r && calc(i, q[l + 1]) < calc(i, q[l]); ++l);
        f[i] = a[i] + (LL(i) * i - i >> 1) + calc(i, q[l]);
        g[i] = f[i] + (LL(i) * i + i >> 1);
        for (; r && (q[r] - q[r - 1]) * (g[i] - g[q[r]]) - (i - q[r]) * (g[q[r]] - g[q[r - 1]]) <= 0; --r);
        q[++r] = i;
        if (l > r)
            l = r;
    }
    printf("%lld\n", f[n]);
    return 0;
}
