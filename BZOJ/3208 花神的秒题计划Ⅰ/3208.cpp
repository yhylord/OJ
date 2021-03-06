#include <cstdio>

const int MAXN = 777, dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

bool b[MAXN][MAXN];
int idx, a[MAXN][MAXN], f[MAXN][MAXN], v[MAXN][MAXN];

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

int dp(int x, int y) {
    if (v[x][y] == idx)
        return f[x][y];
    f[x][y] = 1;
    v[x][y] = idx;
    for (int i = 0; i < 4; ++i) {
        int tx = x + dx[i], ty = y + dy[i];
        if (!b[tx][ty] && a[tx][ty] < a[x][y])
            checkmax(f[x][y], dp(tx, ty) + 1);
    }
    return f[x][y];
}

int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%d", &a[i][j]);
    for (int i = 0; i <= n + 1; ++i)
        for (int j = 0; j <= n + 1; ++j)
            if (!i || i == n + 1 || !j || j == n + 1)
                b[i][j] = true;
    scanf("%d", &m);
    for (idx = 1; idx <= m; ++idx) {
        char op;
        int x, y, p, q;
        scanf(" %c", &op);
        if (op == 'C') {
            scanf("%d%d%d", &x, &y, &p);
            a[x][y] = p;
        }
        else if (op == 'S') {
            scanf("%d%d%d%d", &x, &y, &p, &q);
            for (int i = x; i <= p; ++i)
                for (int j = y; j <= q; ++j)
                    b[i][j] = true;
        }
        else if (op == 'B') {
            scanf("%d%d%d%d", &x, &y, &p, &q);
            for (int i = x; i <= p; ++i)
                for (int j = y; j <= q; ++j)
                    b[i][j] = false;
        }
        else {
            int ans = 0;
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    if (!b[i][j])
                        checkmax(ans, dp(i, j));
            printf("%d\n", ans);
        }
    }
    return 0;
}
