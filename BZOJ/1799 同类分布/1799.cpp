#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

const int MAXN = 22, MAXS = 166;

int cur, idx, a[MAXN], v[2][MAXN][MAXS][MAXS];
LL f[2][MAXN][MAXS][MAXS];

LL calc(bool less, int dep, int sum, int rem) {
    if (!dep)
        return !sum && !rem;
    if (v[less][dep][sum][rem] == idx)
        return f[less][dep][sum][rem];
    v[less][dep][sum][rem] = idx;
    f[less][dep][sum][rem] = 0;
    int ed = min(less ? 9 : a[dep], sum);
    for (int i = max(sum - 9 * (dep - 1), 0); i <= ed; ++i)
        f[less][dep][sum][rem] += calc(less || i < a[dep], dep - 1, sum - i, (rem * 10 + i) % cur);
    return f[less][dep][sum][rem];
}

inline LL get(LL x) {
    LL ret = a[0] = 0;
    for (; x; x /= 10)
        a[++a[0]] = x % 10;
    for (cur = 1; cur <= a[0] * 9; ++cur) {
        ++idx;
        ret += calc(0, a[0], cur, 0);
    }
    return ret;
}

int main() {
    LL x, y;
    scanf("%lld%lld", &x, &y);
    printf("%lld\n", get(y) - get(x - 1));
    return 0;
}
