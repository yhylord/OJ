#include <cstdio>
#include <cstring>

const int MAXN = 55, MAXS = 22222;

int u[MAXN], d[MAXN], f[MAXN][MAXS];

inline void checkmin(int &x, int y) {
    if (y < x)
        x = y;
}

int main() {
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &u[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &d[i]);
    memset(f, 63, sizeof f);
    f[1][0] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= s + u[i]; ++j) {
            if (j < s + u[i])
                checkmin(f[i][j + 1], f[i][j] + d[i]);
            if (j >= u[i])
                checkmin(f[i + 1][j - u[i]], f[i][j] + (j - u[i]) * m);
        }
    printf("%d\n", f[n + 1][0]);
    return 0;
}
