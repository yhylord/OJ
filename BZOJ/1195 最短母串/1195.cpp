#include <cstdio>

const int MAXL = 601, MAXS = 1 << 12;

bool v[MAXL][MAXS];
int q[MAXL * MAXS], lst[MAXL * MAXS];
short msk[MAXL * MAXS], c[MAXL * MAXS], nxt[MAXL][26], p[MAXL], g[MAXL], ans[MAXL];

int main() {
    int n, r = -1, tot = 0;
    scanf("%d%*c", &n);
    for (int i = 0; i < n; ++i) {
        int x = 0;
        for (char c; (c = getchar()) != '\n'; x = nxt[x][c - 'A'])
            if (!nxt[x][c - 'A'])
                nxt[x][c - 'A'] = ++tot;
        g[x] |= 1 << i;
    }
    for (int k = 0; k < 26; ++k)
        if (nxt[0][k])
            q[++r] = nxt[0][k];
    for (int l = 0; l <= r; ++l)
        for (int k = 0; k < 26; ++k) {
            int x = p[q[l]];
            for (; x && !nxt[x][k]; x = p[x]);
            if (nxt[q[l]][k]) {
                p[q[++r] = nxt[q[l]][k]] = nxt[x][k];
                g[q[r]] |= g[p[q[r]]];
            }
            else
                nxt[q[l]][k] = nxt[x][k];
        }
    q[0] = r = 0;
    for (int l = 0; l <= r; ++l)
        for (int k = 0; k < 26; ++k)
            if (!v[nxt[q[l]][k]][msk[l] | g[nxt[q[l]][k]]]) {
                q[++r] = nxt[q[l]][k];
                msk[r] = msk[l] | g[nxt[q[l]][k]];
                lst[r] = l;
                c[r] = k;
                v[q[r]][msk[r]] = true;
                if (msk[r] == (1 << n) - 1) {
                    for (int i = r; i; i = lst[i])
                        ans[++ans[0]] = c[i];
                    for (int i = ans[0]; i; --i)
                        putchar(ans[i] + 'A');
                    putchar('\n');
                    return 0;
                }
            }
    return 0;
}
