#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 111, MAXP = 555;

bool p[MAXP];
int c[MAXN][MAXN], d[MAXP];

struct bigint {
    int a[MAXN];

    inline bigint() {
        a[1] = a[0] = 1;
    }

    inline void operator *= (int x) {
        for (int i = 1; i <= a[0]; ++i)
            a[i] *= x;
        for (int i = 1; i <= a[0]; ++i) {
            a[i + 1] += a[i] / 10;
            a[i] %= 10;
        }
        if (a[a[0] + 1])
            ++a[0];
    }

    inline void print() {
        for (int i = a[0]; i; --i)
            printf("%d", a[i]);
        putchar('\n');
    }
} ans;

int main() {
    int n, m, tot = 0;
    for (int i = 2; i < MAXP; ++i)
        if (!p[i]) {
            d[i] = tot++;
            for (int j = i * i; j < MAXP; j += i)
                p[j] = true;
        }
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int x;
        scanf("%d", &x);
        for (int j = 2; j < MAXP; ++j)
            while (x % j == 0) {
                x /= j;
                c[d[j]][i] ^= 1;
            }
    }
    for (int k = 0, x = 0; k < m; ++k) {
        int t = -1;
        for (int i = x; i < n && !~t; ++i)
            if (c[i][k])
                t = i;
        if (!~t) {
            ans *= 2;
            continue;
        }
        for (int j = k; j <= m; ++j)
            swap(c[x][j], c[t][j]);
        for (int i = x + 1; i < n; ++i)
            if (c[i][k])
                for (int j = k; j <= m; ++j)
                    c[i][j] ^= c[x][j];
        ++x;
    }
    --ans.a[1];
    ans.print();
    return 0;
}
