#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

const int MOD = 1000000007;

inline LL pow(LL x, int p) {
    LL ret = 1;
    for (; p; p >>= 1) {
        if (p & 1)
            (ret *= x) %= MOD;
        (x *= x) %= MOD;
    }
    return ret;
}

int main() {
    LL n, m;
    scanf("%lld%lld", &n, &m);
    if (n < m)
        swap(n, m);
    n %= MOD;
    LL t1 = 1, t2 = 1, ans = (n + 1) % MOD;
    for (int i = 1; i <= m; ++i) {
        (t1 *= n + i) %= MOD;
        (t2 *= i) %= MOD;
        (ans += t1 * pow(t2, MOD - 2)) %= MOD;
    }
    printf("%lld\n", ans);
    return 0;
}
