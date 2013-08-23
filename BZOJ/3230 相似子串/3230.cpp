#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long LL;

const int MAXN = 111111;

int n, q, lg[MAXN];
LL cnt[MAXN];

struct sa {
    char s[MAXN];
    int c[MAXN], sa[MAXN], nsa[MAXN], rk[MAXN], nrk[MAXN][2], ht[MAXN][18];

    inline void build() {
        for (int i = 0; i < n; ++i)
            ++c[s[i]];
        for (int i = 0; i < 333; ++i)
            c[i + 1] += c[i];
        for (int i = n - 1; i >= 0; --i)
            sa[--c[s[i]]] = i;
        rk[sa[0]] = 1;
        for (int i = 1; i < n; ++i)
            rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
        for (int k = 1; k < n && rk[sa[n - 1]] < n; k <<= 1) {
            memset(c, 0, sizeof c);
            for (int i = 0; i < n; ++i) {
                nrk[i][0] = rk[i];
                ++c[nrk[i][1] = i + k < n ? rk[i + k] : 0];
            }
            for (int i = 0; i < n; ++i)
                c[i + 1] += c[i];
            for (int i = n - 1; i >= 0; --i)
                nsa[--c[nrk[i][1]]] = i;
            memset(c, 0, sizeof c);
            for (int i = 0; i < n; ++i)
                ++c[nrk[i][0]];
            for (int i = 0; i < n; ++i)
                c[i + 1] += c[i];
            for (int i = n - 1; i >= 0; --i)
                sa[--c[nrk[nsa[i]][0]]] = nsa[i];
            rk[sa[0]] = 1;
            for (int i = 1; i < n; ++i)
                rk[sa[i]] = rk[sa[i - 1]] + (nrk[sa[i]][0] != nrk[sa[i - 1]][0] || nrk[sa[i]][1] != nrk[sa[i - 1]][1]);
        }
        for (int i = 0, k = 0; i < n; ++i)
            if (--rk[i]) {
                int j = sa[rk[i] - 1];
                for (; i + k < n && j + k < n && s[i + k] == s[j + k]; ++k);
                ht[rk[i]][0] = k ? k-- : k;
            }
        for (int k = 1; k <= lg[n]; ++k)
            for (int i = 0; i + (1 << k) <= n; ++i)
                ht[i][k] = min(ht[i][k - 1], ht[i + (1 << k - 1)][k - 1]);
    }

    inline int lcp(int x, int y) {
        if (x == y)
            return n - x;
        if ((x = rk[x]) > (y = rk[y]))
            swap(x, y);
        int k = lg[y - x];
        return min(ht[x + 1][k], ht[y - (1 << k) + 1][k]);
    }
} a, b;

inline LL sqr(LL x) {
    return x * x;
}

inline void get(LL i, int &x, int &y) {
    int t = lower_bound(cnt + 1, cnt + n + 1, i) - cnt - 1;
    x = a.sa[t], y = x + a.ht[t][0] + i - cnt[t] - 1;
}

int main() {
    scanf("%d%d%s", &n, &q, a.s);
    for (int i = 1; i <= n; ++i) {
        b.s[i - 1] = a.s[n - i];
        lg[i] = lg[i - 1] + (1 << lg[i - 1] + 1 == i);
    }
    a.build(), b.build();
    for (int i = 0; i < n; ++i)
        cnt[i + 1] = cnt[i] + n - a.sa[i] - a.ht[i][0];
    while (q--) {
        LL i, j;
        scanf("%lld%lld", &i, &j);
        if (i > cnt[n] || j > cnt[n]) {
            puts("-1");
            continue;
        }
        int x1, y1, x2, y2;
        get(i, x1, y1), get(j, x2, y2);
        int lim = min(y1 - x1 + 1, y2 - x2 + 1);
        printf("%lld\n", sqr(min(a.lcp(x1, x2), lim)) + sqr(min(b.lcp(n - 1 - y1, n - 1 - y2), lim)));
    }
    return 0;
}
