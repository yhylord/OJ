#include <cstdio>

typedef long long LL;

const int MAXN = 111111, MOD = 1000000007;

bool v[MAXN];
int tot, h[MAXN], p[MAXN << 1], w[MAXN << 1], nxt[MAXN << 1], f[MAXN];
LL ans;

inline void addedge(int x, int y, int z) {
    p[++tot] = y;
    w[tot] = z;
    nxt[tot] = h[x];
    h[x] = tot;
}

void dfs(int x) {
    v[x] = f[x] = 1;
    for (int k = h[x]; k; k = nxt[k])
        if (!v[p[k]]) {
            dfs(p[k]);
            int t = LL(w[k]) * f[p[k]] % MOD;
            ans += LL(t) * f[x] % MOD;
            (f[x] += t) %= MOD;
        }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addedge(x, y, z);
        addedge(y, x, z);
    }
    dfs(1);
    printf("%d\n", ans % MOD);
    return 0;
}
