#include <algorithm>
#include <cstdio>

using namespace std;

int n, a[22][66666];

int main() {
    int m, x, s = 0;
    long long ans = 0;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &x);
        for (int j = 0; j < 16; ++j)
            ++a[j][(x & ((1 << j + 1) - 1)) + 1];
    }
    for (int i = 0; i < 16; ++i)
        for (int j = 1; j <= 1 << 16; ++j)
            a[i][j] += a[i][j - 1];
    while (m--) {
        char c;
        scanf(" %c%d", &c, &x);
        if (c == 'A')
            (s += x) &= (1 << 16) - 1;
        else if (x < 16) {
            int l = 1 << x, r = (1 << x + 1) - 1;
            ans += a[x][min(max(r - (s & ((1 << x + 1) - 1)) + 1, 0), 1 << 16)];
            ans -= a[x][min(max(l - (s & ((1 << x + 1) - 1)), 0), 1 << 16)];
            l += 1 << x + 1, r += 1 << x + 1;
            ans += a[x][min(max(r - (s & ((1 << x + 1) - 1)) + 1, 0), 1 << 16)];
            ans -= a[x][min(max(l - (s & ((1 << x + 1) - 1)), 0), 1 << 16)];
        }
    }
    printf("%lld\n", ans);
    return 0;
}
