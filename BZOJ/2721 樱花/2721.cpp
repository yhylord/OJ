#include <cstdio>
#include <cstring>

typedef long long LL;

const int MAXN = 1000001, MOD = 1000000007;

bool b[MAXN];
int p[MAXN], c[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    memset(b, true, sizeof b);
    for (int i = 2; i <= 1000; ++i)
        if (b[i]) {
            p[++p[0]] = i;
            for (int j = i * i; j < MAXN; j += i)
                b[j] = false;
        }
    for (int i = 1001; i < MAXN; ++i)
        if (b[i])
            p[++p[0]] = i;
    for (int i = 1; i <= p[0]; ++i)
        for (int j = p[i]; j <= n; j += p[i])
            for (int t = j; t % p[i] == 0; t /= p[i], ++c[i]);
    LL ans = 1;
    for (int i = 1; i <= p[0]; ++i)
        (ans *= (c[i] + c[i] + 1)) %= MOD;
    printf("%lld\n", ans);
    return 0;
}
