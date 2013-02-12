#include <cstdio>

const int MAXN = 555, MAXC = 111111;

bool v[MAXC];
int d[MAXC], a[MAXN][MAXN];

int main() {
    for (int i = 2, k = 1; i < MAXC; ++i)
        if (!v[i]) {
            for (; k <= i; ++k)
                d[k] = i - k;
            if (i > MAXC / i)
                continue;
            for (int j = i * i; j < MAXC; j += i)
                v[j] = true;
        }
    int n, m, ans = 1000000000;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        int t = 0;
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
            t += d[a[i][j]];
        }
        if (t < ans)
            ans = t;
    }
    for (int j = 1; j <= m; ++j) {
        int t = 0;
        for (int i = 1; i <= n; ++i)
            t += d[a[i][j]];
        if (t < ans)
            ans = t;
    }
    printf("%d\n", ans);
    return 0;
}
