#include <cstdio>

const int MAXN = 111, MAXM = 111111;

bool f[MAXM];
int a[MAXN], c[MAXN], v[MAXM], s[MAXM];

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) && n) {
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &c[i]);
        for (int i = 0; i <= m; ++i)
            f[i] = v[i] = 0;
        f[0] = true;
        for (int i = 1; i <= n; ++i)
            for (int j = a[i]; j <= m; ++j)
                if (!f[j] && f[j - a[i]])
                    if (v[j - a[i]] != i)
                        f[j] = true, v[j] = i, s[j] = 1;
                    else if (s[j - a[i]] < c[i])
                        f[j] = true, v[j] = i, s[j] = s[j - a[i]] + 1;
        int ans = 0;
        for (int i = 1; i <= m; ++i)
            ans += f[i];
        printf("%d\n", ans);
    }
    return 0;
}
