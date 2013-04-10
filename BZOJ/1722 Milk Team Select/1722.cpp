#include <climits>
#include <cstdio>
#include <cstring>

const int MAXN = 555;

int n, f[MAXN][2][MAXN], g[MAXN], a[MAXN], h[MAXN], nxt[MAXN], s[MAXN];

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

void dp(int x) {
    for (int i = 0; i <= n; ++i)
        f[x][0][i] = f[x][1][i] = INT_MIN / 2;
    s[x] = 1;
    for (int k = h[x]; k; k = nxt[k]) {
        dp(k);
        s[x] += s[k];
    }
    for (int i = 0; i < 2; ++i) {
        f[x][i][0] = i * a[x];
        for (int k = h[x]; k; k = nxt[k]) {
            memcpy(g, f[x][i], sizeof f[x][i]);
            for (int l = 0; l < 2; ++l)
                for (int p = 0; p <= s[k]; ++p)
                    for (int j = p + (i & l); j <= s[x]; ++j)
                        checkmax(g[j], f[x][i][j - p - (i & l)] + f[k][l][p]);
            memcpy(f[x][i], g, sizeof g);
        }
    }
}

int main() {
    int m, x;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &a[i], &x);
        nxt[i] = h[x];
        h[x] = i;
    }
    dp(0);
    for (int i = n; i >= 0; --i)
        if (f[0][0][i] >= m) {
            printf("%d\n", i);
            return 0;
        }
    puts("-1");
    return 0;
}
