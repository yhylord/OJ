#include <cstdio>

int f[1111111], t[1111];

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

int main() {
    int n, l, ans = 0;
    scanf("%d%d", &n, &l);
    for (int i = 1; i <= n; ++i) {
        int x, cur = t[0] = 0;
        scanf("%d", &x);
        for (int j = 1; j * j <= x; ++j)
            if (x % j == 0) {
                int a = j, b = x / j;
                t[++t[0]] = a;
                t[++t[0]] = b;
                if (a >= l)
                    checkmax(cur, f[a]);
                if (b >= l)
                    checkmax(cur, f[b]);
            }
        checkmax(ans, ++cur);
        for (int j = 1; j <= t[0]; ++j)
            checkmax(f[t[j]], cur);
    }
    printf("%d\n", ans);
    return 0;
}
