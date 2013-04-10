#include <cstdio>
#include <cstring>

const int MAXN = 11111;

int a[2][MAXN], c[MAXN], sa[MAXN], rk[MAXN], nsa[MAXN], nrk[MAXN][2];

int main() {
    int n;
    scanf("%d%*d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[0][i]);
        nrk[i][0] = a[0][i];
        ++c[nrk[i][1] = i];
    }
    for (int i = 0; i < n; ++i)
        c[i + 1] += c[i];
    for (int i = n - 1; i >= 0; --i)
        nsa[--c[nrk[i][1]]] = i;
    memset(c, 0, sizeof c);
    for (int i = 0; i < n; ++i)
        ++c[nrk[i][0]];
    for (int i = 0; i < 11; ++i)
        c[i + 1] += c[i];
    for (int i = n - 1; i >= 0; --i)
        sa[--c[nrk[nsa[i]][0]]] = nsa[i];
    rk[sa[0]] = 0;
    for (int i = 1; i < n; ++i)
        rk[sa[i]] = rk[sa[i - 1]] + 1;
    for (int i = 0; i < n; ++i) {
        int p = i & 1, q = p ^ 1;
        for (int j = 0; j < n; ++j)
            a[q][rk[j]] = a[p][j];
        printf(i == n - 1 ? "%d\n" : "%d ", a[q][0]);
    }
    return 0;
}
