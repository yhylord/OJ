#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

const int MOD = 19940417;

inline int sqrsum(int n) {
    int a = n, b = n + 1, c = 2 * n + 1;
    if (a % 3 == 0)
        a /= 3;
    else if (b % 3 == 0)
        b /= 3;
    else
        c /= 3;
    return LL(a) * b / 2 % MOD * c % MOD;
}

inline int calc1(int n, int k) {
    int ret = 0;
    for (int i = 1; i <= k; ++i) {
        int p = n / i, q = min(n / p, k);
        ret = (ret + LL(i + q) * (q - i + 1) / 2 % MOD * p % MOD) % MOD;
        i = q;
    }
    return ret;
}

inline int calc2(int n, int m, int k) {
    int ret = 0;
    for (int i = 1; i <= k; ++i) {
        int p1 = n / i, p2 = m / i, q = min(min(n / p1, m / p2), k);
        ret = (ret + LL(sqrsum(q) - sqrsum(i - 1) + MOD) * p1 % MOD * p2 % MOD) % MOD;
        i = q;
    }
    return ret;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    if (n > m)
        swap(n, m);
    int ans1 = (LL(n) * n - calc1(n, n)) % MOD * ((LL(m) * m - calc1(m, m)) % MOD) % MOD,
        ans2 = ((LL(n) * n % MOD * m % MOD - LL(n) * calc1(m, n) % MOD -
               LL(m) * calc1(n, n) % MOD + calc2(n, m, n)) % MOD + MOD) % MOD;
    printf("%d\n", (ans1 - ans2 + MOD) % MOD);
    return 0;
}
