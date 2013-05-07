#include <cstdio>

const int MAXN = 111111, MAXQ = 66666, MAXL = 366666, MAXC = 128;

char s[MAXN];
int id[MAXQ], nxt[MAXL][MAXC], f[MAXL], p[MAXL], v[MAXL], q[MAXL];

int main() {
    int n, m, tot = 0, r = -1;
    scanf("%d%d%*c", &n, &m);
    for (int i = 1, j = 0; i <= n; ++i)
        while ((s[j++] = getchar()) != '\n');
    for (int i = 0; i < m; ++i) {
        int x = 0;
        for (char c; (c = getchar()) != '\n'; x = nxt[x][c])
            if (!nxt[x][c])
                nxt[x][c] = ++tot;
        id[i] = x;
    }
    for (int k = 0; k < MAXC; ++k)
        if (nxt[0][k])
            q[++r] = nxt[0][k];
    for (int l = 0; l <= r; ++l)
        for (int k = 0; k < MAXC; ++k)
            if (nxt[q[l]][k]) {
                q[++r] = nxt[q[l]][k];
                int x = p[q[l]];
                for (; x && !nxt[x][k]; x = p[x]);
                p[q[r]] = nxt[x][k];
            }
    for (int i = 1, j = -1; i <= n; ++i) {
        int x = 0;
        for (++j; s[j] != '\n'; ++j) {
            for (; x && !nxt[x][s[j]]; x = p[x]);
            for (int t = x = nxt[x][s[j]]; t && v[t] != i; t = p[t]) {
                v[t] = i;
                ++f[t];
            }
        }
    }
    for (int i = 0; i < m; ++i)
        printf("%d\n", f[id[i]]);
    return 0;
}
