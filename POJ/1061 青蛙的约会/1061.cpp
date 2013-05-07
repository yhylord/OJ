#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

LL c;

void exgcd(LL a, LL b, LL &x, LL &y) {
    if (!b) {
        x = c / a, y = 0;
        return;
    }
    LL tx, ty;
    exgcd(b, a % b, tx, ty);
    x = ty, y = tx - a / b * ty;
}

int main() {
    LL x, y, m, n, l;
    scanf("%I64d%I64d%I64d%I64d%I64d", &x, &y, &m, &n, &l);
    c = y - x;
    if (c % __gcd(m - n, l)) {
        puts("Impossible");
        return 0;
    }
    exgcd(m - n, l, x, y);
    LL ans = (x % l + l) % l;
    printf("%I64d\n", ans ? ans : l);
    return 0;
}
