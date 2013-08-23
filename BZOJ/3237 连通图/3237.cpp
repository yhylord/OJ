#include <cstdio>

const int MAXN = 111111;

int f[MAXN], h[MAXN], cur[MAXN << 1], a[MAXN << 1], b[MAXN << 1], c[MAXN][5],
    lst[MAXN][5], nxt[MAXN][5], x[18][MAXN][5], y[18][MAXN][5];

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

void solve(int dep, int cnt, int l, int r) {
    if (l == r) {
        puts(cnt == 1 ? "Connected" : "Disconnected");
        return;
    }
    int mid = l + r >> 1, cur = 0;
    for (int i = 1; i <= cnt; ++i)
        f[i] = i;
    for (int i = mid + 1; i <= r; ++i)
        for (int j = 1; j <= c[i][0]; ++j)
            if (lst[i][j] < l)
                f[find(x[dep][i][j])] = find(y[dep][i][j]);
    for (int i = 1; i <= cnt; ++i)
        if (f[i] == i)
            h[i] = ++cur;
    for (int i = l; i <= mid; ++i)
        for (int j = 1; j <= c[i][0]; ++j) {
            x[dep + 1][i][j] = h[find(x[dep][i][j])];
            y[dep + 1][i][j] = h[find(y[dep][i][j])];
        }
    solve(dep + 1, cur, l, mid);
    cur = 0;
    for (int i = 1; i <= cnt; ++i)
        f[i] = i;
    for (int i = l; i <= mid; ++i)
        for (int j = 1; j <= c[i][0]; ++j)
            if (nxt[i][j] > r)
                f[find(x[dep][i][j])] = find(y[dep][i][j]);
    for (int i = 1; i <= cnt; ++i)
        if (f[i] == i)
            h[i] = ++cur;
    for (int i = mid + 1; i <= r; ++i)
        for (int j = 1; j <= c[i][0]; ++j) {
            x[dep + 1][i][j] = h[find(x[dep][i][j])];
            y[dep + 1][i][j] = h[find(y[dep][i][j])];
        }
    solve(dep + 1, cur, mid + 1, r);
}

int main() {
    int n, m, k, cnt = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d", &a[i], &b[i]);
    scanf("%d", &k);
    for (int i = 1; i <= k; ++i) {
        scanf("%d", &c[i][0]);
        for (int j = 1; j <= c[i][0]; ++j) {
            scanf("%d", &c[i][j]);
            lst[i][j] = cur[c[i][j]];
            cur[c[i][j]] = i;
        }
    }
    for (int i = 1; i <= m; ++i)
        cur[i] = k + 1;
    for (int i = k; i; --i)
        for (int j = 1; j <= c[i][0]; ++j) {
            nxt[i][j] = cur[c[i][j]];
            cur[c[i][j]] = i;
        }
    for (int i = 1; i <= n; ++i)
        f[i] = i;
    for (int i = 1; i <= m; ++i)
        if (cur[i] > k)
            f[find(a[i])] = find(b[i]);
    for (int i = 1; i <= n; ++i)
        if (f[i] == i)
            h[i] = ++cnt;
    for (int i = 1; i <= k; ++i)
        for (int j = 1; j <= c[i][0]; ++j) {
            x[0][i][j] = h[find(a[c[i][j]])];
            y[0][i][j] = h[find(b[c[i][j]])];
        }
    solve(0, cnt, 1, k);
    return 0;
}
