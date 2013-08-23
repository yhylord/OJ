#include <cstdio>

const int MAXN = 222;

char a[MAXN][MAXN];
int f[MAXN][MAXN][MAXN], q[MAXN], p[MAXN];

int main() {
    int n, m, x, y, s, d, ans = 0;
    scanf("%d%d%d%d%d", &n, &m, &x, &y, &s);
    for (int i = 1; i <= n; ++i)
        scanf("%s", a[i] + 1);
    f[0][x][y] = 1;
    for (int t = 1; t <= s; ++t) {
        scanf("%d%d%d", &x, &y, &d);
        x = y - x + 1;
        if (d == 1)
            for (int j = 1; j <= m; ++j) {
                int l = 0, r = -1;
                for (int i = n; i; --i)
                    if (a[i][j] == 'x')
                        l = r + 1;
                    else {
                        for (; l <= r && p[l] - i > x; ++l);
                        if (f[t - 1][i][j]) {
                            for (; l <= r && f[t - 1][i][j] + i > q[r]; --r);                    
                            q[++r] = f[t - 1][i][j] + i, p[r] = i;
                        }
                        if (l <= r)
                            f[t][i][j] = q[l] - i;
                    }
            }
        else if (d == 2)
            for (int j = 1; j <= m; ++j) {
                int l = 0, r = -1;
                for (int i = 1; i <= n; ++i)
                    if (a[i][j] == 'x')
                        l = r + 1;
                    else {
                        for (; l <= r && i - p[l] > x; ++l);
                        if (f[t - 1][i][j]) {
                            for (; l <= r && f[t - 1][i][j] - i > q[r]; --r);                    
                            q[++r] = f[t - 1][i][j] - i, p[r] = i;
                        }
                        if (l <= r)
                            f[t][i][j] = q[l] + i;
                    }
            }
        else if (d == 3)
            for (int i = 1; i <= n; ++i) {
                int l = 0, r = -1;
                for (int j = m; j; --j)
                    if (a[i][j] == 'x')
                        l = r + 1;
                    else {
                        for (; l <= r && p[l] - j > x; ++l);
                        if (f[t - 1][i][j]) {
                            for (; l <= r && f[t - 1][i][j] + j > q[r]; --r);                    
                            q[++r] = f[t - 1][i][j] + j, p[r] = j;
                        }
                        if (l <= r)
                            f[t][i][j] = q[l] - j;
                    }
            }
        else
            for (int i = 1; i <= n; ++i) {
                int l = 0, r = -1;
                for (int j = 1; j <= m; ++j)
                    if (a[i][j] == 'x')
                        l = r + 1;
                    else {
                        for (; l <= r && j - p[l] > x; ++l);
                        if (f[t - 1][i][j]) {
                            for (; l <= r && f[t - 1][i][j] - j > q[r]; --r);                    
                            q[++r] = f[t - 1][i][j] - j, p[r] = j;
                        }
                        if (l <= r)
                            f[t][i][j] = q[l] + j;
                    }
            }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (f[s][i][j] > ans)
                ans = f[s][i][j];
    printf("%d\n", ans - 1);
    return 0;
}
