#include <cstdio>

typedef long long LL;

const int MAXN = 1111111;

bool v[MAXN], e[MAXN];
int tot, q[MAXN << 1], d[MAXN], qu[MAXN << 1], h[MAXN], p[MAXN << 1], w[MAXN << 1], nxt[MAXN << 1];
LL f[MAXN], g[MAXN], s[MAXN << 1];

inline void addedge(int x, int y, int z) {
    ++d[p[++tot] = y], w[tot] = z, nxt[tot] = h[x], h[x] = tot;
}

inline void checkmax(LL &x, LL y) {
    if (y > x)
        x = y;
}

int main() {
    int n, r = -1;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(i, x, y);
        addedge(x, i, y);
    }
    for (int i = 1; i <= n; ++i)
        if (d[i] == 1)
            q[++r] = i;
    for (int l = 0; l <= r; ++l) {
        int x = q[l];
        LL mx = 0;
        v[x] = true;
        for (int k = h[x]; k; k = nxt[k]) {
            int y = p[k];
            if (v[y]) {
                checkmax(g[x], g[y]);
                if (f[y] + w[k] >= f[x])
                    mx = f[x], f[x] = f[y] + w[k];
                else
                    checkmax(mx, f[y] + w[k]);
            }
            else if (--d[y] == 1)
                q[++r] = y;
        }
        checkmax(g[x], f[x] + mx);
    }
    LL ans = 0;
    for (int i = 1; i <= n; ++i)
        if (!v[i]) {
            int lst = 0, le = 0, ri = 0;
            LL tmp = 0;
            q[r = 0] = i;
            for (int l = 0; l <= r; ++l) {
                int x = q[l];
                LL mx = 0;
                bool b = e[x] = v[x] = true;
                for (int k = h[x]; k; k = nxt[k]) {
                    int y = p[k];
                    if (v[y] && !e[y]) {
                        checkmax(g[x], g[y]);
                        if (f[y] + w[k] >= f[x])
                            mx = f[x], f[x] = f[y] + w[k];
                        else
                            checkmax(mx, f[y] + w[k]);
                    }
                    else if (!v[y] && b)
                        q[++r] = y, s[r] = w[k], b = false;
                    else if (!v[y] && !b)
                        lst = w[k];
                }
                checkmax(g[x], f[x] + mx);
                checkmax(tmp, g[x]);
            }
            for (int l = 0; l <= r; ++l)
                q[l + r + 1] = q[l], s[l + r + 1] = s[l];
            s[r + 1] = lst, qu[0] = 0;
            for (int l = 1; l <= r + r + 1; ++l) {
                s[l] += s[l - 1];
                for (; l - qu[le] > r; ++le);
                checkmax(tmp, f[q[qu[le]]] - s[qu[le]] + f[q[l]] + s[l]);
                for (; le <= ri && f[q[l]] - s[l] > f[q[qu[ri]]] - s[qu[ri]]; --ri);
                qu[++ri] = l;
            }
            ans += tmp;
        }
    printf("%lld\n", ans);
    return 0;
}
