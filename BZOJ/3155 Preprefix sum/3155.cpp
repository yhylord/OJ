#include <cstdio>

typedef long long LL;

const int MAXN = 111111;

char op[11];
int n, a[MAXN];

struct bit {
    LL s[MAXN];

    inline void add(int x, LL v) {
        for (; x <= n; x += x & -x)
            s[x] += v;
    }

    inline LL sum(int x) {
        LL ret = 0;
        for (; x; x -= x & -x)
            ret += s[x];
        return ret;
    }
} b1, b2;

int main() {
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        b1.add(i, a[i]);
        b2.add(i, LL(n - i + 1) * a[i]);
    }
    while (m--) {
        int i, x;
        scanf("%s%d", op, &i);
        if (op[0] == 'Q')
            printf("%lld\n", b2.sum(i) - b1.sum(i) * (n - i));
        else {
            scanf("%d", &x);
            b1.add(i, x - a[i]);
            b2.add(i, LL(n - i + 1) * (x - a[i]));
            a[i] = x;
        }
    }
    return 0;
}
