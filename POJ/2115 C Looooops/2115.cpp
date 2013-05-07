#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

void exgcd(LL a, LL b, LL c, LL &x, LL &y) {
    if (!b) {
        x = c / a, y = 0;
        return;
    }
    LL tx, ty;
    exgcd(b, a % b, c, tx, ty);
    x = ty, y = tx - a / b * ty;
}

int main() {
    LL a, b, c, k;
    while (scanf("%I64d%I64d%I64d%I64d", &a, &b, &c, &k) && a + b + c + k) {
        LL m = 1LL << k, d = __gcd(c, m);
        if ((b - a) % d)
            puts("FOREVER");
        else {
            LL x, y;
            exgcd(c, m, b - a, x, y);
            m /= d;
            printf("%I64d\n", (x % m + m) % m);
        }
    }
    return 0;
}
