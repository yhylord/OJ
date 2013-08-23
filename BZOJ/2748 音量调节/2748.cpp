#include <cstdio>

bool f[55][1111];

int main() {
    int n, bg, mx, ans = -1;
    scanf("%d%d%d", &n, &bg, &mx);
    f[0][bg] = true;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        for (int j = 0; j <= mx; ++j)
            if (f[i][j]) {
                if (j + x >= 0 && j + x <= mx)
                    f[i + 1][j + x] = true;
                if (j - x >= 0 && j - x <= mx)
                    f[i + 1][j - x] = true;
            }
    }
    for (int i = 0; i <= mx; ++i)
        if (f[n][i])
            ans = i;
    printf("%d\n", ans);
    return 0;
}
