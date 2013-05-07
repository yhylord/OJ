#include <cstdio>

const int MAXN = 10, MAXS = 1 << MAXN - 1;

int m, n;
long long f[MAXN][MAXS];

void dfs(int no, int dep, int s1, int s2, int b1, int b2) {
    if (dep == n) {
        f[no][s1] += f[no - 1][s2];
        return;
    }
    if (dep < n - 1) {
        if (!b1) {
            dfs(no, dep + 1, (s1 << 1) + 1, (s2 << 1) + 1 - b2, 1, 0);
            dfs(no, dep + 1, (s1 << 1) + 1, (s2 << 1) + 1 - b2, 1, 1);
        }
        if (!b2)
            dfs(no, dep + 1, (s1 << 1) + b1, s2 << 1, 1, 1);
        if (!b1 && !b2) {
            dfs(no, dep + 1, (s1 << 1) + 1, s2 << 1, 1, 0);
            dfs(no, dep + 1, (s1 << 1) + 1, s2 << 1, 0, 1);
        }
    }
    if (!b1 && !b2)
        dfs(no, dep + 1, (s1 << 1) + 1, s2 << 1, 0, 0);
    dfs(no, dep + 1, (s1 << 1) + b1, (s2 << 1) + 1 - b2, 0, 0);
}

int main() {
    scanf("%d%d", &m, &n);
    f[0][(1 << n) - 1] = 1;
    for (int i = 1; i <= m; ++i)
        dfs(i, 0, 0, 0, 0, 0);
    printf("%I64d\n", f[m][(1 << n) - 1]);
    return 0;
}
