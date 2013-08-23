#include <cstdio>

const int T = 12, MAXP = 20, MAXN = 50, MOD = 10000;

int n, t[MAXP], a[MAXP][4];

struct matrix {
    int a[MAXN][MAXN];

    inline matrix() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                a[i][j] = 0;
            a[i][i] = 1;
        }
    }
} b[T + 1], c, u, w;

inline matrix operator *(const matrix &x, const matrix &y) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            w.a[i][j] = 0;
            for (int k = 0; k < n; ++k)
                w.a[i][j] += x.a[i][k] * y.a[k][j] % MOD;
            w.a[i][j] %= MOD;
        }
    return w;
}

inline matrix pow(matrix x, int y) {
    matrix z;
    for (; y; y >>= 1) {
        if (y & 1)
            z = z * x;
        x = x * x;
    }
    return z;
}

int main() {
    int m, p, bg, ed, k;
    scanf("%d%d%d%d%d", &n, &m, &bg, &ed, &k);
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        u.a[x][y] = u.a[y][x] = 1;
    }
    scanf("%d", &p);
    for (int i = 0; i < p; ++i) {
        scanf("%d", &t[i]);
        for (int j = 0; j < t[i]; ++j)
            scanf("%d", &a[i][j]);
    }
    b[0] = matrix();
    for (int i = 1; i <= T; ++i) {
        c = u;
        for (int j = 0; j < p; ++j) {
            int x = a[j][i % t[j]];
            for (int k = 0; k < n; ++k)
                c.a[k][x] = 0;
        }
        b[i] = b[i - 1] * c;
    }
    printf("%d\n", (pow(b[T], k / T) * b[k % T]).a[bg][ed]);
    return 0;
}
