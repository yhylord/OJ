#include <cstdio>

const int MAXN = 33, MAXL = 9, MOD = 1000000007;

int f[MAXN][MAXN][1 << MAXL][MAXL];

inline void inc(int &x, int y) {
    if ((x += y) >= MOD)
        x -= MOD;
}

int main() {
    int n, m, l;
    scanf("%d%d%d", &n, &m, &l);
    f[2][0][0][0] = 1;
    for (int i = 2; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            for (int s = 0; s < 1 << l + 1; ++s) {
                for (int k = 0; k < l; ++k)
                    if (f[i][j][s][k]) {
                        inc(f[i][j][s][k + 1], f[i][j][s][k]);
                        if (j < m && i + k - l > 0)
                            inc(f[i][j + 1][s ^ (1 << k) ^ (1 << l)][k], f[i][j][s][k]);
                    }
                if (!(s & 1) && f[i][j][s][l])
                    inc(f[i + 1][j][s >> 1][0], f[i][j][s][l]);
            }
    printf("%d\n", f[n + 1][m][0][0]);
    return 0;
}
