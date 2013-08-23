#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 2222222, MAXM = 222222, MAXQ = 11111;

int n, m, idx, v[MAXN], ans[MAXM], s[MAXN];

struct query {
    int op, x1, y1, x2, y2;

    inline query(int _op = 0, int _x1 = 0, int _y1 = 0, int _x2 = 0, int _y2 = 0): op(_op), x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
} q[MAXM], a[MAXQ];

inline bool operator <(const query &x, const query &y) {
    return x.x1 < y.x1;
}

inline void add(int x, int p) {
    for (; x <= n; x += x & -x)
        if (v[x] == idx)
            s[x] += p;
        else
            s[x] = p, v[x] = idx;
}

inline int sum(int x) {
    int ret = 0;
    for (; x; x -= x & -x)
        ret += v[x] == idx ? s[x] : 0;
    return ret;
}

void solve(int l, int r) {
    if (l == r) {
        if (q[l].op == 2)
            printf("%d\n", ans[l]);
        return;
    }
    int mid = l + r >> 1, tot = 0;
    solve(l, mid);
    sort(q + l, q + mid + 1);
    for (int i = mid + 1; i <= r; ++i)
        if (q[i].op == 2) {
            a[tot++] = query(-1, q[i].x1 - 1, q[i].y1, i, q[i].y2);
            a[tot++] = query(1, q[i].x2, q[i].y1, i, q[i].y2);
        }
    sort(a, a + tot);
    ++idx;
    for (int i = 0, j = l; i < tot; ++i) {
        for (; j <= mid && q[j].x1 <= a[i].x1; ++j)
            if (q[j].op == 1)
                add(q[j].y1, q[j].x2);
        ans[a[i].x2] += a[i].op * (sum(a[i].y2) - sum(a[i].y1 - 1));
    }
    solve(mid + 1, r);
}

int main() {
    scanf("%*d%d", &n);
    while (scanf("%d", &q[++m].op) && q[m].op != 3) {
        scanf("%d%d%d", &q[m].x1, &q[m].y1, &q[m].x2);
        if (q[m].op == 2)
            scanf("%d", &q[m].y2);
    }
    solve(1, --m);
    return 0;
}
