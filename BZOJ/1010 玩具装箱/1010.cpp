#include <cstdio>

typedef long long LL;

const int MAXN = 55555;

int t, c[MAXN], q[MAXN], p[MAXN];
LL s[MAXN], f[MAXN];

inline LL sqr(LL x) {
    return x * x;
}

inline LL calc(int i, int j) {
    return f[i] + sqr(j - i - 1 + s[j] - s[i] - t);
}

int main() {
    int n, l = 1, r = 1;
    scanf("%d%d", &n, &t);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &c[i]);
        s[i] = s[i - 1] + c[i];
    }
    p[1] = n;
    for (int i = 1; i <= n; ++i) {
        for (; i > p[l]; ++l);
        f[p[l - 1] = i] = calc(q[l], i);
        for (; l <= r && calc(i, p[r - 1] + 1) < calc(q[r], p[r - 1] + 1); --r);
        if (l <= r) {
            int lo = p[r - 1] + 1, hi = p[r] + 1;
            while (lo + 1 < hi) {
                int mid = lo + hi >> 1;
                if (calc(i, mid) < calc(q[r], mid))
                    hi = mid;
                else
                    lo = mid;
            }
            p[r] = lo;
        }
        if (p[r] < n)
            q[++r] = i, p[r] = n;
    }
    printf("%lld\n", f[n]);
    return 0;
}
