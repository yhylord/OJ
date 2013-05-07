#include <cstdio>

const int MAXN = 4444, MAXM = MAXN * MAXN >> 1, MAXS = 66;

bool in[MAXN];
int tot, cnt, idx, s[MAXN], c[MAXN], d[MAXN], q[MAXN], dfn[MAXN], low[MAXN],
    g[MAXN][MAXN], size[MAXN], f[MAXN][MAXS], h[MAXN], p[MAXM], nxt[MAXM];

inline void checkmin(int &x, int y) {
    if (y < x)
        x = y;
}

inline void addedge(int x, int y) {
    p[++tot] = y;
    nxt[tot] = h[x];
    h[x] = tot;
}

void tarjan(int x) {
    in[s[++s[0]] = x] = true;
    dfn[x] = low[x] = ++idx;
    for (int k = h[x]; k; k = nxt[k])
        if (!dfn[p[k]]) {
            tarjan(p[k]);
            checkmin(low[x], low[p[k]]);
        }
        else if (in[p[k]])
            checkmin(low[x], dfn[p[k]]);
    if (low[x] == dfn[x]) {
        ++cnt;
        do {
            c[s[s[0]]] = cnt;
            in[s[s[0]]] = false;
        } while (s[s[0]--] != x);
    }
}

int main() {
    int n, r = -1, ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf(" ");
        for (int j = 1; j <= n; ++j)
            if (getchar() == '1')
                addedge(i, j);
    }
    cnt = n;
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; ++i) {
        ++size[c[i]];
        for (int k = h[i]; k; k = nxt[k])
            if (c[i] != c[p[k]] && !g[c[i]][c[p[k]]]) {
                addedge(c[i], c[p[k]]);
                g[c[i]][c[p[k]]] = true;
                ++d[c[p[k]]];
            }
    }
    for (int i = n + 1; i <= cnt; ++i) {
        int j = i - n - 1;
        f[i][j >> 5] = 1 << (j & 31);
        if (!d[i])
            q[++r] = i;
    }
    for (int l = 0; l <= r; ++l)
        for (int k = h[q[l]]; k; k = nxt[k])
            if (!--d[p[k]])
                q[++r] = p[k];
    for (; r >= 0; --r)
        for (int k = h[q[r]]; k; k = nxt[k])
            for (int i = 0; i < MAXS; ++i)
                f[q[r]][i] |= f[p[k]][i];
    for (int i = n + 1; i <= cnt; ++i) {
        int t = 0;
        for (int j = 0; j < cnt - n; ++j)
            if (f[i][j >> 5] & (1 << (j & 31)))
                t += size[n + j + 1];
        ans += size[i] * t;
    }
    printf("%d\n", ans);
    return 0;
}
