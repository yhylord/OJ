#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 111111;

int n, m, a[MAXN], f[MAXN], s[MAXN];

struct data {
    int x, y, w;

    inline data(int _x = 0, int _y = 0, int _w = 0): x(_x), y(_y), w(_w) {}

    inline bool operator <(const data &t) const {
        return x < t.x || x == t.x && y < t.y;
    }
} d[MAXN];

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

inline void update(int x, int v) {
    for (; x <= m; x += x & -x)
        checkmax(s[x], v);
}

inline int query(int x) {
    int ret = 0;
    for (; x; x -= x & -x)
        checkmax(ret, s[x]);
    return ret;
}

int main() {
    scanf("%*d%d", &n);
    for (int i = 0; i < n; ++i) {
        int t, p, v;
        scanf("%d%d%d", &t, &p, &v);
        d[i] = data(2 * t - p, 2 * t + p, v);
        a[m++] = 2 * t + p;
    }
    sort(a, a + m);
    m = unique(a, a + m) - a;
    sort(d, d + n);
    for (int i = 0; i < n; ++i) {
        int p = lower_bound(a, a + m, d[i].y) - a + 1;
        update(p, f[i] = query(p) + d[i].w);
    }
    printf("%d\n", query(m));
    return 0;
}
