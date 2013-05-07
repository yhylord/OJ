#include <cstdio>
#include <cstring>

const int MAXN = 55, MAXL = 111, BASE = 1000000000;

struct bigint {
    int a[15];

    inline bigint(int x = 0) {
        memset(a, 0, sizeof a);
        a[0] = 1;
        a[1] = x;
    }

    inline bool positive() {
        return a[0] == 1 && a[1] || a[0] > 1;
    }

    inline void operator += (bigint x) {
        if (x.a[0] > a[0])
            a[0] = x.a[0];
        for (int i = 1; i <= a[0]; ++i) {
            a[i + 1] += (a[i] += x.a[i]) / BASE;
            a[i] %= BASE;
        }
        if (a[a[0] + 1])
            ++a[0];
    }

    inline void print() {
        printf("%d", a[a[0]]);
        for (int i = a[0] - 1; i; --i)
            printf("%09d", a[i]);
        putchar('\n');
    }
} f[MAXN][MAXL], ans;

bool g[MAXL];
int id[256], p[MAXL], q[MAXL], nxt[MAXL][MAXN];

int main() {
    int n, m, w, tot = 0, r = -1;
    scanf("%d%d%d%*c", &n, &m, &w);
    for (int k = 0; k < n; ++k)
        id[getchar()] = k;
    for (getchar(); w--; ) {
        int x = 0;
        for (unsigned char c; (c = getchar()) != '\n'; x = nxt[x][id[c]])
            if (!nxt[x][id[c]])
                nxt[x][id[c]] = ++tot;
        g[x] = true;
    }
    for (int k = 0; k < n; ++k)
        if (nxt[0][k])
            q[++r] = nxt[0][k];
    for (int l = 0; l <= r; ++l)
        for (int k = 0; k < n; ++k) {
            int x = p[q[l]];
            for (; x && !nxt[x][k]; x = p[x]);
            if (nxt[q[l]][k]) {
                p[q[++r] = nxt[q[l]][k]] = nxt[x][k];
                g[q[r]] |= g[p[q[r]]];
            }
            else
                nxt[q[l]][k] = nxt[x][k];
        }
    f[0][0] = bigint(1);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j <= tot; ++j)
            if (f[i][j].positive())
                for (int k = 0; k < n; ++k)
                    if (!g[nxt[j][k]])
                        f[i + 1][nxt[j][k]] += f[i][j];
    for (int j = 0; j <= tot; ++j)
        ans += f[m][j];
    ans.print();
    return 0;
}
