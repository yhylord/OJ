#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 333, MAXC = 1111;

long double fac[MAXN], a[MAXN][MAXN], b[MAXN][MAXN], p[MAXN][MAXN], q[MAXN][MAXN];
int c[MAXN], h[MAXC];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &c[i]);
        ++h[c[i]];
    }
    for (int i = 1; i <= 1000; ++i)
        h[i] += h[i - 1];
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i;
    for (int i = 0; i < n - 1; ++i) {
        p[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            p[i][j] = p[i][j - 1] * (i - j + 1);
        for (int j = 0; j <= i; ++j)
            p[i][j] = p[i][j] * fac[n - j - 2] * (j + 1);
        a[i][0] = p[i][0];
        for (int j = 1; j <= i; ++j)
            a[i][j] = a[i][j - 1] + p[i][j];
    }
    for (int i = 0; i < n; ++i) {
        q[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            q[i][j] = q[i][j - 1] * (i - j + 1);
        for (int j = 0; j <= i; ++j)
            q[i][j] = q[i][j] * fac[n - j - 1] * (j + 1);
        b[i][0] = q[i][0];
        for (int j = 1; j <= i; ++j)
            b[i][j] = b[i][j - 1] + q[i][j];
    }
    long double ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 2; j <= n; ++j)
            ans = ans + a[h[c[i] - 1]][min(j - 2, h[c[i] - 1])] * (n - h[c[i] - 1] - 1);
        ans = ans + b[h[c[i] - 1]][h[c[i] - 1]];
    }
    for (int i = 1; i <= n; ++i)
        ans /= i;
    printf("%.2lf\n", double(ans));
    return 0;
}
