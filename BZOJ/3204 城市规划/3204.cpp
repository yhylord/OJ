#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 222222, MAXB = 5555, MAXT = 2222222;

bool co[MAXT], oe[MAXT], ro[MAXB][7];
char a[MAXN][7], ra[MAXB][7];
int n, m, size, cnt, que, f[MAXT], v[MAXT], no[MAXT], rf[MAXB][7], id[MAXN][7], b[MAXN], cur[MAXB];

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

inline int build(int bg, int ed, int c1, int c2) {
    for (int i = bg; i < ed; ++i)
        for (int j = 0; j < m; ++j) {
            f[id[i][j]] = id[i][j];
            oe[id[i][j]] = co[id[i][j]] = false;
        }
    for (int i = bg; i < ed; ++i)
        for (int j = 0; j < m; ++j) {
            int x = find(id[i][j]);
            if (a[i][j] == '+' || a[i][j] == '|') {
                if (i > bg && a[i - 1][j] != '.' && a[i - 1][j] != '-')
                    f[find(id[i - 1][j])] = x;
                if (i < ed - 1 && a[i + 1][j] != '.' && a[i + 1][j] != '-')
                    f[find(id[i + 1][j])] = x;
            }
            if (a[i][j] == '+' || a[i][j] == '-') {
                if (j && a[i][j - 1] != '.' && a[i][j - 1] != '|')
                    f[find(id[i][j - 1])] = x;
                if (j < m - 1 && a[i][j + 1] != '.' && a[i][j + 1] != '|')
                    f[find(id[i][j + 1])] = x;
            }
            if (a[i][j] == 'O') {
                if (i > bg && a[i - 1][j] == 'O')
                    f[find(id[i - 1][j])] = x;
                if (j && a[i][j - 1] == 'O')
                    f[find(id[i][j - 1])] = x;
            }
        }
    for (int i = bg; i < ed; ++i)
        for (int j = 0; j < m; ++j) {
            if (i == bg || i == ed - 1)
                oe[find(id[i][j])] = true;
            if (a[i][j] == 'O')
                co[find(id[i][j])] = true;
        }
    for (int i = 0; i < m; ++i) {
        rf[c1][i] = find(id[bg][i]);
        rf[c2][i] = find(id[ed - 1][i]);
        ro[c1][i] = co[rf[c1][i]];
        ro[c2][i] = co[rf[c2][i]];
        ra[c1][i] = a[bg][i];
        ra[c2][i] = a[ed - 1][i];
    }
    int ret = 0;
    for (int i = bg; i < ed; ++i)
        for (int j = 0; j < m; ++j)
            if (f[id[i][j]] == id[i][j] && !oe[id[i][j]] && co[id[i][j]])
                ++ret;
    return ret;
}

inline int query(int l, int r) {
    int ret = 0, tot = cnt << 1;
    if (b[l] == b[r])
        ret += build(l, r + 1, tot, tot + 1), tot += 2;
    else {
        ret += build(l, (b[l] + 1) * size, tot, tot + 1), tot += 2;
        for (int i = b[l] + 1; i < b[r]; ++i) {
            ret += cur[i];
            memcpy(ro[tot], ro[i << 1], sizeof ro[i << 1]);
            memcpy(rf[tot], rf[i << 1], sizeof rf[i << 1]);
            memcpy(ra[tot++], ra[i << 1], sizeof ra[i << 1]);
            memcpy(ro[tot], ro[(i << 1) + 1], sizeof ro[(i << 1) + 1]);
            memcpy(rf[tot], rf[(i << 1) + 1], sizeof rf[(i << 1) + 1]);
            memcpy(ra[tot++], ra[(i << 1) + 1], sizeof ra[(i << 1) + 1]);
        }
        ret += build(b[r] * size, r + 1, tot, tot + 1), tot += 2;
    }
    int idx = n * m;
    for (int i = cnt << 1; i < tot; ++i)
        for (int j = 0; j < m; ++j)
            if (v[rf[i][j]] != que) {
                v[rf[i][j]] = que;
                no[rf[i][j]] = idx++;
            }
    for (int i = n * m; i < idx; ++i)
        co[f[i] = i] = false;
    for (int i = (cnt << 1) + 1; i < tot - 1; i += 2)
        for (int j = 0; j < m; ++j)
            if (ra[i][j] != '.' && ra[i + 1][j] != '.' && ra[i][j] != '-' && ra[i + 1][j] != '-' &&
                (ra[i][j] == 'O' && ra[i + 1][j] == 'O' || ra[i][j] == '|' || ra[i][j] == '+' || ra[i + 1][j] == '|' || ra[i + 1][j] == '+'))
                f[find(no[rf[i][j]])] = find(no[rf[i + 1][j]]);
    for (int i = cnt << 1; i < tot; ++i)
        for (int j = 0; j < m; ++j)
            co[find(no[rf[i][j]])] |= ro[i][j];
    for (int i = n * m; i < idx; ++i)
        if (f[i] == i && co[i])
            ++ret;
    return ret;
}

int main() {
    scanf("%d%d", &n, &m);
    size = int(sqrt(n));
    cnt = n / size + (n % size != 0);
    for (int i = 0; i < n; ++i) {
        scanf("%s", a[i]);
        b[i] = i / size;
        for (int j = 0; j < m; ++j)
            id[i][j] = i * m + j;
    }
    for (int i = 0; i < cnt; ++i) {
        int bg = i * size, ed = min(bg + size, n);
        cur[i] = build(bg, ed, i << 1, (i << 1) + 1);
    }
    int q;
    scanf("%d", &q);
    for (que = 1; que <= q; ++que) {
        char op;
        int x, y;
        scanf(" %c%d%d", &op, &x, &y);
        --x, --y;
        if (op == 'C') {
            scanf(" %c", &a[x][y]);
            int t = b[x], bg = t * size, ed = min(bg + size, n);
            cur[t] = build(bg, ed, t << 1, (t << 1) + 1);
        }
        else
            printf("%d\n", query(x, y));
    }
    return 0;
}
