#include <cstdio>
#include <cstring>

const int MAXN = 5555;

int f[22][MAXN][2], g[22][MAXN][2];

inline void checkmax(int &x, int y) {
    if (!~x || y > x)
        x = y;
}

inline void checkmin(int &x, int y) {
    if (!~x || y < x)
        x = y;
}

int main() {
    int n, mx = -1, mn = 111111;
    scanf("%d", &n);
    memset(f, -1, sizeof f);
    memset(g, -1, sizeof g);
    f[0][0][0] = g[0][0][0] = 0;
    f[0][1][1] = g[0][1][1] = 1;
    for (int i = 1; 1 << i <= n + 1; ++i)
        for (int j = 1; j <= n; ++j) {
            for (int l = 0; l * 2 + 1 <= j; ++l)
                if (~f[i][l][0] && ~f[i][j - l - 1][0]) {
                    checkmin(f[i][j][1], f[i][l][0] + f[i][j - l - 1][0] + 1);
                    checkmax(g[i][j][1], g[i][l][0] + g[i][j - l - 1][0] + 1);
                }
            for (int l = 0; l * 2 + 1 <= j; ++l)
                for (int p = 0; p < 2; ++p)
                    for (int q = 0; q < 2; ++q)
                        if (~f[i - 1][l][p] && ~f[i - 1][j - l - 1][q]) {
                            checkmin(f[i][j][0], f[i - 1][l][p] + f[i - 1][j - l - 1][q]);
                            checkmax(g[i][j][0], g[i - 1][l][p] + g[i - 1][j - l - 1][q]);
                        }
            for (int k = 0; k < 2; ++k) {
                if (j == n && ~f[i][j][k])
                    checkmin(mn, f[i][j][k]);
                if (j == n && ~g[i][j][k])
                    checkmax(mx, g[i][j][k]);
            }
        }
    printf("%d\n%d\n", mn, mx);
    return 0;
}
