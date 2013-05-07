#include <cstdio>
#include <cstring>

typedef long long LL;

const int MAXN = 222222;

bool v[MAXN], e[MAXN], b[MAXN << 1], mk[MAXN << 1];
int rt, tot, r, q[MAXN], h[MAXN], p[MAXN << 1], w[MAXN << 1], nxt[MAXN << 1];
LL f[MAXN], g[MAXN];

inline void addedge(int x, int y, int z) {
    p[tot] = y;
    w[tot] = z;
    mk[tot] = true;
    nxt[tot] = h[x];
    h[x] = tot++;
}

inline void bfs(int bg) {
    memset(v, false, sizeof v);
    memset(b, false, sizeof b);
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    r = 0;
    v[q[r] = bg] = true;
    for (int l = 0; l <= r; ++l)
        for (int k = h[q[l]]; ~k; k = nxt[k])
            if (!v[p[k]] && mk[k]) {
                b[k] = true;
                v[q[++r] = p[k]] = true;
            }
    for (int i = r; i >= 0; --i) {
        int x = q[i];
        for (int k = h[x]; ~k; k = nxt[k])
            if (b[k]) {
                LL t = w[k] + f[p[k]];
                if (t > f[x]) {
                    g[x] = f[x];
                    f[x] = t;
                }
                else if (t > g[x])
                    g[x] = t;
            }
        if (f[x] + g[x] > f[rt] + g[rt])
            rt = x;
    }
}

int main() {
    int n, ans = 0;
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; ++i) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        z <<= 1;
        addedge(x, y, z);
        addedge(y, x, z);
    }
    bfs(1);
    printf("%lld\n", f[rt] + g[rt] >> 1);
    for (LL len1 = f[rt], len2 = g[rt]; ; ) {
        if (len1 <= len2)
            break;
        for (int k = h[rt]; ~k; k = nxt[k])
            if (b[k] && w[k] + f[p[k]] == len1) {
                len1 -= w[k];
                len2 += w[k];
                if (len1 < len2) {
                    int t = rt;
                    rt = n + 1;
                    addedge(rt, t, (len1 + len2 >> 1) - len1);
                    addedge(rt, p[k], (len1 + len2 >> 1) - len1);
                    ans = -1;
                    mk[k] = mk[k ^ 1] = false;
                }
                else
                    rt = p[k];
                break;
            }
    }
    bfs(rt);
    int c1 = 0, c2 = 0;
    for (int k = h[rt]; ~k; k = nxt[k])
        if (b[k]) {
            c1 += w[k] + f[p[k]] == f[rt];
            c2 += w[k] + f[p[k]] == g[rt];
        }
    if (f[rt] == g[rt]) {
        if (c1 > 2) {
            puts("0");
            return 0;
        }
        ans += 2;
        for (int k = h[rt]; ~k; k = nxt[k])
            if (b[k] && w[k] + f[p[k]] == f[rt])
                e[p[k]] = true;
    }
    else {
        if (c1 == 1) {
            ++ans;
            for (int k = h[rt]; ~k; k = nxt[k])
                if (b[k] && w[k] + f[p[k]] == f[rt])
                    e[p[k]] = true;
        }
        if (c2 == 1) {
            ++ans;
            for (int k = h[rt]; ~k; k = nxt[k])
                if (b[k] && w[k] + f[p[k]] == g[rt])
                    e[p[k]] = true;
        }
    }
    for (int i = 0; i <= r; ++i)
        if (e[q[i]]) {
            int c = 0, x = q[i];
            for (int k = h[x]; ~k; k = nxt[k])
                if (b[k] && w[k] + f[p[k]] == f[x])
                    ++c;
            if (c == 1) {
                ++ans;
                for (int k = h[x]; ~k; k = nxt[k])
                    if (b[k] && w[k] + f[p[k]] == f[x])
                        e[p[k]] = true;
            }
        }
    printf("%d\n", ans);
    return 0;
}
