#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 2222;

char s[MAXN], g[33];
int c[MAXN], ht[MAXN], sa[MAXN], nsa[MAXN], rk[MAXN], nrk[MAXN][2];

int main() {
    gets(s);
    gets(g);
    int n = strlen(s), m;
    scanf("%d", &m);
    for (int i = 0; i < n; ++i)
        ++c[s[i]];
    for (int i = 0; i < 333; ++i)
        c[i + 1] += c[i];
    for (int i = n - 1; i >= 0; --i)
        sa[--c[s[i]]] = i;
    rk[sa[0]] = 1;
    for (int i = 1; i < n; ++i)
        rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    for (int k = 1; k < n; k <<= 1) {
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
            while (i + k < n && j + k < n && s[i + k] == s[j + k])
                ++k;
            ht[rk[i]] = k ? k-- : k;
        }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = 0, t = 0;
        while (sa[i] + j < n && (t += (g[s[sa[i] + j] - 'a'] - 48) ^ 1) <= m)
            ++j;
        ans += max(j - ht[i], 0);
    }
    printf("%d\n", ans);
    return 0;
}
