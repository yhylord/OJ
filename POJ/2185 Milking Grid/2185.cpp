#include <cstdio>
#include <cstring>

const int MAXN = 11111, MAXM = 77;

bool v[MAXN];
char s[MAXN][MAXM];
int c[MAXN], p[MAXN];

int main() {
    int n, m, a, b;
    scanf("%d%d ", &n, &m);
    for (int i = 1; i <= n; ++i)
        gets(s[i] + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 2, k = 0; j <= m; ++j) {
            while (k && s[i][j] != s[i][k + 1])
                k = p[k];
            p[j] = k += s[i][j] == s[i][k + 1];
        }
        memset(v, false, sizeof v);
        for (int j = m; j; j = p[j]) {
            int l = m - p[j];
            for (int k = l; k <= m; k += l)
                v[k] = true;
        }
        for (int j = 1; j <= m; ++j)
            c[j] += v[j];
    }
    for (a = 1; c[a] != n && a <= m; ++a);
    memset(c, 0, sizeof c);
    for (int i = 1; i <= m; ++i) {
        for (int j = 2, k = 0; j <= n; ++j) {
            while (k && s[j][i] != s[k + 1][i])
                k = p[k];
            p[j] = k += s[j][i] == s[k + 1][i];
        }
        memset(v, false, sizeof v);
        for (int j = n; j; j = p[j]) {
            int l = n - p[j];
            for (int k = l; k <= n; k += l)
                v[k] = true;
        }
        for (int j = 1; j <= n; ++j)
            c[j] += v[j];
    }
    for (b = 1; c[b] != m && b <= n; ++b);
    printf("%d\n", a * b);
    return 0;
}
