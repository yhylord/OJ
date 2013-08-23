#include <cstdio>
#include <cstring>

typedef long long LL;

LL n, m, g, u[2], v[2][2], w[2][2];

inline LL mul(LL x, LL y) {
    LL ret = 0;
    for (; y; y >>= 1) {
        if (y & 1)
            (ret += x) %= m;
        (x <<= 1) %= m;
    }
    return ret;
}

int main() {
    scanf("%lld%lld%lld%lld%lld%lld", &m, &v[0][0], &u[1], &u[0], &n, &g);
    v[0][1] = v[1][1] = 1;
    for (; n; n >>= 1) {
        if (n & 1) {
            memset(w[0], 0, sizeof w[0]);
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j)
                    (w[0][i] += mul(v[i][j], u[j])) %= m;
            memcpy(u, w[0], sizeof w[0]);
        }
        memset(w, 0, sizeof w);
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                    (w[i][j] += mul(v[i][k], v[k][j])) %= m;
        memcpy(v, w, sizeof w);
    }
    printf("%d\n", u[0] % g);
    return 0;
}
