#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 1111;

int a[MAXN], b[MAXN], c[MAXN], f[MAXN][MAXN], g[MAXN][MAXN];

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

int main() {
    int n, q;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
        c[i] = min(c[i], 1000 / a[i]);
    }
    for (int i = 1; i <= n; ++i) {
        for (int k = 0; k <= 1000; ++k)
            f[i][k] = f[i - 1][k];
        for (int m = 1, t = c[i]; t; m <<= 1) {
            if (m > t)
                m = t;
            t -= m;
            for (int k = 1000; k >= m * a[i]; --k)
                checkmax(f[i][k], f[i][k - m * a[i]] + m * b[i]);
        }
    }
    for (int i = n; i; --i) {
        for (int k = 0; k <= 1000; ++k)
            g[i][k] = g[i + 1][k];
        for (int m = 1, t = c[i]; t; m <<= 1) {
            if (m > t)
                m = t;
            t -= m;
            for (int k = 1000; k >= m * a[i]; --k)
                checkmax(g[i][k], g[i][k - m * a[i]] + m * b[i]);
        }
    }
    scanf("%d", &q);
    while (q--) {
        int d, e, ans = 0;
        scanf("%d%d", &d, &e);
        for (int i = 0; i <= e; ++i)
            checkmax(ans, f[d][i] + g[d + 2][e - i]);
        printf("%d\n", ans);
    }
    return 0;
}
