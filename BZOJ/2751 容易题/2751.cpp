#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

const int MAXN = 111111, MOD = 1000000007;

pair<int, int> a[MAXN];

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
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < k; ++i)
        scanf("%d%d", &a[i].first, &a[i].second);
    sort(a, a + k);
    LL ans = 1, sum = n * LL(n + 1) / 2, tmp = sum;
    for (int i = 0; i < k; ++i)
        if (a[i].first != a[i + 1].first) {
            (ans *= (tmp - a[i].second) % MOD) %= MOD;
            --m, tmp = sum;
        }
        else if (a[i].second != a[i + 1].second)
            tmp -= a[i].second;
    printf("%lld\n", ans * pow(sum % MOD, m) % MOD);
    return 0;
}
