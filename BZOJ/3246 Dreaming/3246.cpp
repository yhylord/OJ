#include <cstdio>
#include <cstring>

const int MAXN = 111111;

bool v[MAXN], got;
int tot, cur, u, lst[3], s[MAXN], go[MAXN], mx[MAXN], h[MAXN], p[MAXN << 1], w[MAXN << 1], nxt[MAXN << 1];

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

inline void addedge(int x, int y, int z) {
    p[++tot] = y, w[tot] = z, nxt[tot] = h[x], h[x] = tot;
}

void dfs1(int x, int sum) {
    if (sum > mx[u])
        mx[u] = sum, go[u] = x;
    v[x] = true;
    for (int k = h[x]; k; k = nxt[k])
        if (!v[p[k]])
            dfs1(p[k], sum + w[k]);
}

void dfs2(int x, int dep, int sum) {
    if (sum == mx[u] && !got) {
        got = true;
        for (int i = 1; i <= dep; ++i)
            checkmax(cur, s[i] <= mx[u] >> 1 ? s[i] : mx[u] - s[i]);
        checkmax(cur, mx[u] - cur);
    }
    v[x] = true;
    for (int k = h[x]; k; k = nxt[k])
        if (!v[p[k]])
            dfs2(p[k], dep + 1, s[dep + 1] = sum + w[k]);
}

int main() {
    int n, m, l, ans = 0, cnt = 0;
    scanf("%d%d%d", &n, &m, &l);
    while (m--) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addedge(x, y, z), addedge(y, x, z);
    }
    for (u = 0; u < n; ++u)
        if (!v[u])
            dfs1(u, 0);
    memset(v, false, sizeof v);
    for (u = 0; u < n; ++u)
        if (!v[u])
            dfs1(go[u], 0);
    memset(v, false, sizeof v);
    for (u = 0; u < n; ++u)
        if (!v[u]) {
            ++cnt, cur = got = false;
            dfs2(go[u], 0, 0);
            checkmax(ans, mx[u]);
            for (int i = 0; i < 3; ++i)
                if (cur > lst[i]) {
                    for (int j = 2; j > i; --j)
                        lst[j] = lst[j - 1];
                    lst[i] = cur;
                    break;
                }
        }
    if (cnt > 1)
        checkmax(ans, lst[0] + lst[1] + l);
    if (cnt > 2)
        checkmax(ans, lst[1] + lst[2] + (l << 1));
    printf("%d\n", ans);
    return 0;
}
