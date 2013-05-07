#include <cstdio>

typedef long long LL;

const int MAXS = 222, MAXN = 11;

int n, s[MAXS], c[MAXS];
LL f[MAXN][MAXS][MAXS];

void dfs(int dep, int cur, int cnt) {
    if (dep == n) {
        s[++s[0]] = cur;
        c[s[0]] = cnt;
        return;
    }
    dfs(dep + 1, cur << 1, cnt);
    if (!(cur & 1))
        dfs(dep + 1, (cur << 1) + 1, cnt + 1);
}

int main() {
    int m;
    scanf("%d%d", &n, &m);
    dfs(0, 0, 0);
    f[0][1][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= s[0]; ++j)
            for (int k = 1; k <= s[0]; ++k)
                if (!(s[k] & s[j]) && !(s[k] & (s[j] >> 1)) && !(s[k] & (s[j] << 1)))
                    for (int t = c[j]; t <= m; ++t)
                        f[i][j][t] += f[i - 1][k][t - c[j]];
    LL ans = 0;
    for (int i = 1; i <= s[0]; ++i)
        ans += f[n][i][m];
    printf("%I64d\n", ans);
    return 0;
}
