#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long LL;

int a[19], c[2522], t[2522][10], d[255][10];
LL f[19][55][255];

LL calc(bool l, int e, int p, int r) {
    if (!e)
        return r % p == 0;
    if (l && ~f[e][c[p]][r])
        return f[e][c[p]][r];
    int u = l ? 9 : a[e];
    LL s = 0;
    for (int i = 0; i <= u; ++i)
        s += calc(l || i < a[e], e - 1, t[p][i], e == 1 ? r * 10 + i : d[r][i]);
    return l ? f[e][c[p]][r] = s : s;
}

inline LL get(LL x) {
    a[0] = 0;
    for (; x; x /= 10)
        a[++a[0]] = x % 10;
    return calc(0, a[0], 1, 0);
}

int main() {
    memset(f, -1, sizeof f);
    for (int i = 1, j = -1; i <= 2520; ++i)
        if (2520 % i == 0)
            c[i] = ++j;
    for (int i = 1; i <= 2520; ++i)
        for (int j = 0; j < 10; ++j)
            t[i][j] = j ? i * j / __gcd(i, j) : i;
    for (int i = 0; i < 252; ++i)
        for (int j = 0; j < 10; ++j)
            d[i][j] = (i * 10 + j) % 252;
    int t;
    scanf("%d", &t);
    while (t--) {
        LL x, y;
        scanf("%lld%lld", &x, &y);
        printf("%lld\n", get(y) - get(x - 1));
    }
    return 0;
}
