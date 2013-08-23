#include <cstdio>

typedef long double LD;
typedef long long LL;

const int MAXN = 1111111;

int a, b, c, q[MAXN];
LL s[MAXN], f[MAXN], g[MAXN];

inline LL calc(int i, int j) {
    return g[j] - 2 * a * s[i] * s[j];
}

int main() {
    int n, l = 0, r = 0;
    scanf("%d%d%d%d", &n, &a, &b, &c);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        s[i] = s[i - 1] + x;
        for (; l < r && calc(i, q[l + 1]) > calc(i, q[l]); ++l);
        f[i] = calc(i, q[l]) + a * s[i] * s[i] + b * s[i] + c;
        g[i] = f[i] + a * s[i] * s[i] - b * s[i];
        for (; r && LD(g[q[r]] - g[q[r - 1]]) / (s[q[r]] - s[q[r - 1]]) <= LD(g[i] - g[q[r]]) / (s[i] - s[q[r]]); --r);
        q[++r] = i;
        if (l > r)
            l = r;
    }
    printf("%lld\n", f[n]);
    return 0;
}
