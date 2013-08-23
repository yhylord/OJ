#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef long double LD;

const LD INF = 1e18;
const int MAXN = 111111;

char str[33];
LD f[MAXN];
int t, v, a[MAXN], s[MAXN], p[MAXN], q[MAXN];

inline LD pow(int x) {
    LD ret = 1;
    for (int i = 1; i <= v; ++i, ret *= x);
    return ret;
}

inline LD calc(int i, int j) {
    return f[i] + pow(abs(j - i - 1 + s[j] - s[i] - t));
}

inline void work() {
    int n, l = 1, r = 1;
    scanf("%d%d%d", &n, &t, &v);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", str);
        s[i] = s[i - 1] + (a[i] = strlen(str));
    }
    p[0] = q[1] = 0, p[1] = n;
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
    if (f[n] <= INF)
        printf("%lld\n", (long long)f[n]);
    else
        puts("Too hard to arrange");
    puts("--------------------");
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--)
        work();
    return 0;
}
