#include <cstdio>

const int MAXN = 222222;

int c[MAXN], d[MAXN], e[MAXN], f[MAXN], s[MAXN][2], q[MAXN], h[MAXN], nxt[MAXN];

inline void checkmin(int &x, int y) {
    if (y < x)
        x = y;
}

int main() {
    int n, r = 0;
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        nxt[i] = h[x];
        h[x] = i;
    }
    q[0] = 1;
    for (int l = 0; l <= r; ++l)
        for (int k = h[q[l]]; k; k = nxt[k])
            c[q[++r] = k] = c[q[l]] ^ 1;
    for (int i = r; i >= 0; --i) {
        int x = q[i];
        if (!h[x])
            s[x][0] = s[x][1] = f[d[x] = e[x] = x] = 1;
        else {
            s[x][c[x]] = e[x] = n + 1;
            for (int k = h[x]; k; k = nxt[k])
                for (int j = 0; j < 2; ++j)
                    if (c[x] == j)
                        checkmin(s[x][j], s[k][j]);
                    else
                        s[x][j] += s[k][j];
            for (int k = h[x]; k; k = nxt[k])
                if (s[k][c[x]] == s[x][c[x]]) {
                    d[x] ^= d[k];
                    checkmin(e[x], e[k]);
                    f[x] += f[k];
                }
        }
    }
    printf("%d %d %d\n", e[1], f[1], d[1]);
    return 0;
}
