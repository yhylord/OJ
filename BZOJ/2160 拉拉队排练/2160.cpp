#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

const int MAXN = 1111111, MOD = 19930726;

char a[MAXN];
int s[MAXN], r[MAXN];

inline int sqr(int x) {
    return LL(x) * x % MOD;
}

int pow(int x, int p) {
    return !p ? 1 : p % 2 ? sqr(pow(x, p / 2)) * LL(x) % MOD : sqr(pow(x, p / 2));
}

int main() {
    int n;
    LL k;
    scanf("%d%lld ", &n, &k);
    a[0] = '$';
    gets(a + 1);
    a[++n] = '#';
    int p = 0, mx = 0;
    for (int i = 1; i < n; ++i) {
        r[i] = mx > i ? min(r[2 * p - i], mx - i) : 1;
        for (; a[i - r[i]] == a[i + r[i]]; ++r[i]);
        if (i + r[i] > mx) {
            p = i;
            mx = i + r[i];
        }
    }
    for (int i = 1; i < n; ++i) {
        ++s[1];
        --s[2 * r[i]];
    }
    LL cnt = 0;
    for (int i = 1; i < n; ++i) {
        s[i] += s[i - 1];
        if (i & 1)
            cnt += s[i];
    }
    if (cnt < k) {
        puts("-1");
        return 0;
    }
    LL ans = 1;
    for (int i = n - 1 - n % 2; k && i; i -= 2) {
        int t = min(LL(s[i]), k);
        (ans *= pow(i, t)) %= MOD;
        k -= t;
    }
    printf("%lld\n", ans);
    return 0;
}
