#include <cstdio>

const int MAXS = 66, MAXN = 111;

int m, a[MAXN], s[MAXS], c[MAXS], f[MAXN][MAXS][MAXS];

void dfs(int dep, int cur, int cnt) {
    if (dep == m) {
        s[++s[0]] = cur;
        c[s[0]] = cnt;
        return;
    }
    dfs(dep + 1, cur << 1, cnt);
    if (!(cur & 1) && !((cur >> 1) & 1))
        dfs(dep + 1, (cur << 1) + 1, cnt + 1);
}

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

int main() {
    int n, ans = 0;
    scanf("%d%d", &n, &m);
    for (int i = 2; i <= n + 1; ++i) {
        scanf(" ");
        for (int j = 0; j < m; ++j)
            a[i] |= (getchar() == 'H') << j;
    }
    dfs(0, 0, 0);
    f[0][1][1] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= s[0]; ++j)
            if (!(s[j] & a[i + 1]))
                for (int k = 1; k <= s[0]; ++k)
                    if (!(s[k] & a[i]) && !(s[j] & s[k]))
                        for (int l = 1; l <= s[0]; ++l)
                            if (!(s[l] & a[i - 1]) && !(s[j] & s[l]) && !(s[k] & s[l]))
                                checkmax(f[i][j][k], f[i - 1][k][l] + c[j]);
    for (int i = 1; i <= s[0]; ++i)
        for (int j = 1; j <= s[0]; ++j)
            checkmax(ans, f[n][i][j]);
    printf("%d\n", ans);
    return 0;
}
