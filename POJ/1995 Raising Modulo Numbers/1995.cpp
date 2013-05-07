#include <cstdio>

int MOD;

inline int pow(int x, int p) {
    int ret = 1, t = x;
    for (; p; p >>= 1) {
        if (p & 1)
            (ret *= t) %= MOD;
        (t *= t) %= MOD;
    }
    return ret;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, ans = 0;
        scanf("%d%d", &MOD, &n);
        while (n--) {
            int a, b;
            scanf("%d%d", &a, &b);
            ans += pow(a % MOD, b);
        }
        printf("%d\n", ans % MOD);
    }
    return 0;
}
