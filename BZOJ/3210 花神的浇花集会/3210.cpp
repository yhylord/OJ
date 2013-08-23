#include <algorithm>
#include <climits>
#include <cstdio>

using namespace std;

typedef long long LL;

const int MAXN = 111111;

int x[MAXN], y[MAXN];
LL mx[2], my[2];

inline void checkmin(LL &x, LL y) {
    if (y < x)
        x = y;
}

int main() {
    int n;
    scanf("%d", &n);
    LL sx = 0, sy = 0;
    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        x[i] = a + b, y[i] = a - b;
        sx += x[i], sy += y[i];
    }
    sort(x, x + n);
    mx[0] = mx[1] = LONG_LONG_MAX;
    LL tx = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 1 || x[i] - x[i - 1] > 1)
            checkmin(mx[(x[i] & 1) ^ 1], LL(i) * (x[i] - 1) - tx + sx - LL(n - i) * (x[i] - 1));
        sx -= x[i];
        checkmin(mx[x[i] & 1], LL(i) * x[i] - tx + sx - LL(n - i - 1) * x[i]);
        tx += x[i];
        if (i == n - 1 || x[i + 1] - x[i] > 1)
            checkmin(mx[(x[i] & 1) ^ 1], LL(i + 1) * (x[i] + 1) - tx + sx - LL(n - i - 1) * (x[i] + 1));
    }
    sort(y, y + n);
    my[0] = my[1] = LONG_LONG_MAX;
    LL ty = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 1 || y[i] - y[i - 1] > 1)
            checkmin(my[(y[i] & 1) ^ 1], LL(i) * (y[i] - 1) - ty + sy - LL(n - i) * (y[i] - 1));
        sy -= y[i];
        checkmin(my[y[i] & 1], LL(i) * y[i] - ty + sy - LL(n - i - 1) * y[i]);
        ty += y[i];
        if (i == n - 1 || y[i + 1] - y[i] > 1)
            checkmin(my[(y[i] & 1) ^ 1], LL(i + 1) * (y[i] + 1) - ty + sy - LL(n - i - 1) * (y[i] + 1));
    }
    printf("%lld\n", min(mx[0] + my[0], mx[1] + my[1]) >> 1);
    return 0;
}
