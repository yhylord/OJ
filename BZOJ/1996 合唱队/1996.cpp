#include <cstdio>

const int MAXN = 1111, MOD = 19650827;

int a[MAXN], f[MAXN][MAXN][2];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        f[i][i][0] = 1;
    }
    for (int k = 1; k < n; ++k)
        for (int i = 1; i + k <= n; ++i) {
            int j = i + k;
            for (int p = 0; p < 2; ++p) {
                if (a[j] > (p ? a[j - 1] : a[i]))
                    (f[i][j][1] += f[i][j - 1][p]) %= MOD;
                if (a[i] < (p ? a[j] : a[i + 1]))
                    (f[i][j][0] += f[i + 1][j][p]) %= MOD;
            }
        }
    printf("%d\n", (f[1][n][0] + f[1][n][1]) % MOD);
    return 0;
}
