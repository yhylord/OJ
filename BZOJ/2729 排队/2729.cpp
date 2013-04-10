#include <cstdio>
#include <cstring>

const int MAXN = 5555, BASE = 10000;

bool p[MAXN];
int c[MAXN];

struct bigint {
    int a[MAXN];

    inline bigint() {
        memset(a, 0, sizeof a);
        a[0] = a[1] = 1;
    }

    inline void operator += (const bigint &x) {
        if (x.a[0] > a[0])
            a[0] = x.a[0];
        for (int i = 1; i <= a[0]; ++i) {
            a[i] += x.a[i];
            a[i + 1] += a[i] / BASE;
            a[i] %= BASE;
        }
        if (a[a[0] + 1])
            ++a[0];
    }

    inline void operator *= (const int &x) {
        for (int i = 1; i <= a[0]; ++i)
            a[i] *= x;
        for (int i = 1; i <= a[0]; ++i) {
            a[i + 1] += a[i] / BASE;
            a[i] %= BASE;
        }
        if (a[a[0] + 1])
            ++a[0];
    }

    inline void print() {
        printf("%d", a[a[0]]);
        for (int i = a[0] - 1; i; --i)
            printf("%04d", a[i]);
        printf("\n");
    }
} a, b;

inline void calc(bigint &a, int n, int m) {
    if (m < 0 || m > n) {
        memset(a.a, 0, sizeof a.a);
        a.a[0] = 1;
        return;
    }
    for (int i = 2; i <= n; ++i)
        if (p[i])
            for (int j = i; j <= n; j += i)
                for (int t = j; t % i == 0; ++c[i], t /= i);
    for (int i = 2; i <= m; ++i)
        if (p[i])
            for (int j = i; j <= m; j += i)
                for (int t = j; t % i == 0; --c[i], t /= i);
    for (int i = 2; i <= n - m; ++i)
        if (p[i])
            for (int j = i; j <= n - m; j += i)
                for (int t = j; t % i == 0; --c[i], t /= i);
    for (int i = 2; i <= n; ++i)
        for (; c[i] > 0; a *= i, --c[i]);
}

inline void fac(int n) {
    for (int i = 1; i <= n; ++i)
        a *= i;
}

int main() {
    memset(p, true, sizeof p);
    p[1] = false;
    for (int i = 2; i < MAXN; ++i)
        if (p[i])
            for (int j = i * i; j < MAXN; j += i)
                p[j] = false;
    int n, m;
    scanf("%d%d", &n, &m);
    calc(a, n + 1, 2);
    calc(a, n + 3, m);
    calc(b, n + 1, 1);
    calc(b, n + 2, m - 1);
    a += b;
    fac(n);
    fac(m);
    a *= 2;
    a.print();
    return 0;
}
