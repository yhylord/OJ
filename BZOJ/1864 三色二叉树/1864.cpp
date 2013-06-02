#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 11111;

int tot = 1, e[MAXN][3], f[MAXN][3], g[MAXN][3];

void dp(int x) {
    e[x][0] = getchar() - 48;
    if (!e[x][0]) {
        f[x][0] = g[x][0] = 1;
        return;
    }
    for (int i = 1; i <= e[x][0]; ++i) {
        e[x][i] = ++tot;
        dp(tot);
    }
    g[x][0] = g[x][1] = g[x][2] = MAXN;
    if (e[x][0] == 1)
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (j != i) {
                    f[x][i] = max(f[x][i], f[e[x][1]][j] + !i);
                    g[x][i] = min(g[x][i], g[e[x][1]][j] + !i);
                }
    if (e[x][0] == 2)
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k)
                    if (j != i && k != i && j != k) {
                        f[x][i] = max(f[x][i], f[e[x][1]][j] + f[e[x][2]][k] + !i);
                        g[x][i] = min(g[x][i], g[e[x][1]][j] + g[e[x][2]][k] + !i);
                    }
}

int main() {
    dp(1);
    printf("%d %d\n", max(max(f[1][0], f[1][1]), f[1][2]), min(min(g[1][0], g[1][1]), g[1][2]));
    return 0;
}
