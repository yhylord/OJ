#include <cstdio>

const int MAXN = 4444, MAXM = MAXN * MAXN >> 1;

bool in[MAXN];
int tot, cnt, idx, s[MAXN], v[MAXN], c[MAXN], dfn[MAXN], low[MAXN],
    g[MAXN][MAXN], size[MAXN], f[MAXN], h[MAXN], p[MAXM], nxt[MAXM];

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

void dfs(int x) {
    v[x] = idx;
    f[x] = size[x];
    for (int k = h[x]; k; k = nxt[k])
        if (v[p[k]] != idx) {
            dfs(p[k]);
            f[x] += f[p[k]];
        }
}

int main() {
    int n, ans = 0;
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
            }
    }
    for (int i = n + 1; i <= cnt; ++i) {
        idx = i;
        dfs(i);
        ans += f[i] * size[i];
    }
    printf("%d\n", ans);
    return 0;
}
