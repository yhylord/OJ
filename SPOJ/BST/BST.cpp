#include <cstdio>

const int MAXN = 333333;

int a[MAXN], p[MAXN], f[MAXN], fa[MAXN], pre[MAXN], nxt[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        p[a[i]] = i;
        pre[i] = i - 1;
        nxt[i] = i + 1;
    }
    nxt[n] = 0;
    for (int i = n; i; --i) {
        int x = pre[a[i]], y = nxt[a[i]];
        fa[i] = p[x] > p[y] ? p[x] : p[y];
        nxt[x] = y;
        pre[y] = x;
    }
    long long ans = 0;
    f[0] = -1;
    for (int i = 1; i <= n; ++i)
        printf("%lld\n", ans += f[i] = f[fa[i]] + 1);
    return 0;
}
