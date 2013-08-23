#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 1111111;

char s[MAXN];
int b[MAXN], c[MAXN], l[MAXN], lg[MAXN], ht[MAXN][22], sa[MAXN], nsa[MAXN], rk[MAXN], nrk[MAXN][2];

inline int lcp(int i, int j) {
    if (i > j)
        swap(i, j);
    int k = lg[j - i];
    return min(ht[i + 1][k], ht[j - (1 << k) + 1][k]);
}

int main() {
    int n, m = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", s + (b[i] = m));
        m += l[i] = strlen(s + m);
        s[m++] = '#';
    }
    for (int i = 2; i <= m; ++i)
        lg[i] = lg[i - 1] + (1 << lg[i - 1] + 1 == i);
    for (int i = 0; i < m; ++i)
        ++c[s[i]];
    for (int i = 0; i < 333; ++i)
        c[i + 1] += c[i];
    for (int i = m - 1; i >= 0; --i)
        sa[--c[s[i]]] = i;
    rk[sa[0]] = 1;
    for (int i = 1; i < m; ++i)
        rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    for (int k = 1; k < m && rk[sa[m - 1]] < m; k <<= 1) {
        memset(c, 0, sizeof c);
        for (int i = 0; i < m; ++i) {
            nrk[i][0] = rk[i];
            ++c[nrk[i][1] = i + k < m ? rk[i + k] : 0];
        }
        for (int i = 0; i < m; ++i)
            c[i + 1] += c[i];
        for (int i = m - 1; i >= 0; --i)
            nsa[--c[nrk[i][1]]] = i;
        memset(c, 0, sizeof c);
        for (int i = 0; i < m; ++i)
            ++c[nrk[i][0]];
        for (int i = 0; i < m; ++i)
            c[i + 1] += c[i];
        for (int i = m - 1; i >= 0; --i)
            sa[--c[nrk[nsa[i]][0]]] = nsa[i];
        rk[sa[0]] = 1;
        for (int i = 1; i < m; ++i)
            rk[sa[i]] = rk[sa[i - 1]] + (nrk[sa[i]][0] != nrk[sa[i - 1]][0] || nrk[sa[i]][1] != nrk[sa[i - 1]][1]);
    }
    for (int i = 0, k = 0; i < m; ++i)
        if (--rk[i]) {
            int j = sa[rk[i] - 1];
            for (; i + k < m && j + k < m && s[i + k] == s[j + k]; ++k);
            ht[rk[i]][0] = k ? k-- : k;
        }
    for (int k = 1; k <= lg[m]; ++k)
        for (int i = 0; i + (1 << k) <= m; ++i)
            ht[i][k] = min(ht[i][k - 1], ht[i + (1 << k - 1)][k - 1]);
    for (int i = 0; i < n; ++i) {
        int cur = rk[b[i]], ans = 0, f = -1, t = cur;
        while (f + 1 < t) {
            int mid = f + t >> 1;
            if (lcp(cur, mid) >= l[i])
                t = mid;
            else
                f = mid;
        }
        ans -= t, f = cur, t = m;
        while (f + 1 < t) {
            int mid = f + t >> 1;
            if (lcp(cur, mid) >= l[i])
                f = mid;
            else
                t = mid;
        }
        printf("%d\n", ans + f + 1);
    }
    return 0;
}
