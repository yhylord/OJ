#include <cstdio>
#include <cstring>

const int MAXN = 555555;

int nxt[MAXN][26], s[MAXN], p[MAXN], q[MAXN];

int main() {
    int t, n;
    for (scanf("%d", &t); t--; ) {
        int tot = 0, r = -1, x, ans = 0;
        memset(nxt[0], 0, sizeof nxt[0]);
        for (scanf("%d", &n); n--; ) {
            scanf(" ");
            x = 0;
            for (char c; (c = getchar()) != '\n'; x = nxt[x][c - 'a'])
                if (!nxt[x][c - 'a']) {
                    nxt[x][c - 'a'] = ++tot;
                    memset(nxt[tot], s[tot] = 0, sizeof nxt[tot]);
                }
            ++s[x];
        }
        for (int i = 0; i < 26; ++i)
            if (nxt[0][i]) {
                q[++r] = nxt[0][i];
                p[q[r]] = 0;
            }
        for (int l = 0; l <= r; ++l)
            for (int i = 0; i < 26; ++i)
                if (nxt[q[l]][i]) {
                    q[++r] = nxt[q[l]][i];
                    for (x = p[q[l]]; x && !nxt[x][i]; x = p[x]);
                    p[q[r]] = nxt[x][i];
                }
        scanf(" ");
        x = 0;
        for (char c; (c = getchar()) != '\n'; ) {
            for (; x && !nxt[x][c - 'a']; x = p[x]);
            for (int t = x = nxt[x][c - 'a']; t && ~s[t]; t = p[t]) {
                ans += s[t];
                s[t] = -1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
