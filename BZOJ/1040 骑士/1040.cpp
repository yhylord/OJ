#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

const int MAXN = 1111111;

bool v[MAXN], e[MAXN];
int tot, a[MAXN], d[MAXN], q[MAXN], h[MAXN], p[MAXN << 1], nxt[MAXN << 1];
LL f[MAXN][2], g[MAXN][2][2];

inline void addedge(int x, int y) {
    ++d[p[++tot] = y], nxt[tot] = h[x], h[x] = tot;
}

int main() {
    int n, r = -1;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d%d", &a[i], &x);
        addedge(i, x);
        addedge(x, i);
    }
    for (int i = 1; i <= n; ++i)
        if (d[i] == 1)
            q[++r] = i;
    for (int l = 0; l <= r; ++l) {
        int x = q[l];
        f[x][1] = a[x];
        v[x] = true;
        for (int k = h[x]; k; k = nxt[k]) {
            int y = p[k];
            if (v[y]) {
                f[x][1] += f[y][0];
                f[x][0] += max(f[y][0], f[y][1]);
            }
            else if (--d[y] == 1)
                q[++r] = y;
        }
    }
    LL ans = 0;
    for (int i = 1; i <= n; ++i)
        if (!v[i]) {
            q[r = 0] = i;
            for (int l = 0; l <= r; ++l) {
                int x = q[l];
                f[x][1] = a[x];
                bool b = v[x] = e[x] = true;
                for (int k = h[x]; k; k = nxt[k]) {
                    int y = p[k];
                    if (v[y] && !e[y]) {
                        f[x][1] += f[y][0];
                        f[x][0] += max(f[y][0], f[y][1]);
                    }
                    else if (!v[y] && b)
                        q[++r] = y, b = false;
                }
            }
            g[0][0][0] = f[q[0]][0];
            g[0][1][1] = f[q[0]][1];
            for (int l = 1; l <= r; ++l)
                for (int k = 0; k < 2; ++k) {
                    g[l][k][0] = max(g[l - 1][k][0], g[l - 1][k][1]) + f[q[l]][0];
                    g[l][k][1] = g[l - 1][k][0] + f[q[l]][1];
                }
            ans += max(g[r][1][0], max(g[r][0][0], g[r][0][1]));
        }
    printf("%lld\n", ans);
    return 0;
}
