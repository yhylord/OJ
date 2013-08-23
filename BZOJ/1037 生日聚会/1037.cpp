#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int MAXN = 155, MAXK = 22, MOD = 12345678;

int k, f[MAXN][MAXN][MAXK][MAXK];

inline void inc(int &x, int y) {
    if ((x += y) >= MOD)
        x -= MOD;
}

inline void update(int i, int j, int p, int q, int x) {
    if (abs(i - j + p) <= k && abs(i - j - q) <= k)
        inc(i - j < 0 ? f[i][j][max(j - i, p)][q] : f[i][j][p][max(i - j, q)], x);
}

int main() {
    int n, m, ans = 0;
    scanf("%d%d%d", &n, &m, &k);
    f[0][0][0][0] = 1;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            for (int p = 0; p <= k; ++p)
                for (int q = 0; q <= k; ++q)
                    if (f[i][j][p][q]) {
                        update(i + 1, j, p, q, f[i][j][p][q]);
                        update(i, j + 1, p, q, f[i][j][p][q]);
                        if (i == n && j == m)
                            inc(ans, f[i][j][p][q]);
                    }
    printf("%d\n", ans);
    return 0;
}
