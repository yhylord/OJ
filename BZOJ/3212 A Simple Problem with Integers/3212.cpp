#include <cstdio>

typedef long long LL;

const int MAXN = 111111;

int n;
LL a[MAXN];

struct bit {
    LL s[MAXN];

    inline void add(int x, int v) {
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

inline void update(int x, int v) {
    if (x)
        b1.add(x, x * v), b2.add(1, v), b2.add(x, -v);
}

inline LL query(int x) {
    return x ? b1.sum(x) + b2.sum(x) * x : 0;
}

int main() {
    char op;
    int q, x, y, z;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &x), a[i] = a[i - 1] + x;
    while (q--) {
        scanf(" %c%d%d", &op, &x, &y);
        if (op == 'C')
            scanf("%d", &z), update(y, z), update(x - 1, -z);
        else
            printf("%lld\n", a[y] - a[x - 1] + query(y) - query(x - 1));
    }
    return 0;
}
