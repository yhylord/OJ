#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
    int n, m, p, x;
    scanf("%d%d%d", &n, &m, &p);
    for (--p; --n; ) {
        scanf("%d", &x);
        p = __gcd(p, x - 1);
    }
    while (p % 2 == 0)
        p >>= 1;
    long long ans = 0;
    for (x = 1; x * x <= p; ++x)
        if (p % x == 0) {
            int a = x, b = p / x;
            if (a != b)
                for (; a <= m; a <<= 1)
                    ans += m - a;
            for (; b <= m; b <<= 1)
                ans += m - b;
        }
    printf("%I64d\n", ans);
    return 0;
}
