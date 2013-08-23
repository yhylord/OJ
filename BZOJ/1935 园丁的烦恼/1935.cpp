#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 555555, MAXM = 2222222;

int b[MAXM], s[MAXM], ans[MAXN];
pair<int, int> a[MAXN];

struct query {
    int p, x, y, z, id;

    inline query() {}

    inline query(int _p, int _x, int _y, int _z, int _id): p(_p), x(_x), y(_y), z(_z), id(_id) {}

    inline bool operator <(const query &t) const {
        return x < t.x;
    }
} q[MAXM];

inline void add(int x) {
    for (; x <= b[0]; x += x & -x)
        ++s[x];
}

inline int sum(int x) {
    int ret = 0;
    for (; x; x -= x & -x)
        ret += s[x];
    return ret;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a[i].first, &a[i].second);
        b[++b[0]] = a[i].second;
    }
    sort(a, a + n);
    for (int i = 0; i < m; ++i) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        q[i] = query(-1, x1 - 1, y1 - 1, y2, i);
        q[m + i] = query(1, x2, y1 - 1, y2, i);
        b[++b[0]] = y1 - 1;
        b[++b[0]] = y2;
    }
    m <<= 1;
    sort(q, q + m);
    sort(b + 1, b + b[0] + 1);
    b[0] = unique(b + 1, b + b[0] + 1) - b - 1;
    for (int i = 0, j = 0; i < m; ++i) {
        for (; j < n && a[j].first <= q[i].x; ++j)
            add(lower_bound(b + 1, b + b[0] + 1, a[j].second) - b);
        ans[q[i].id] += q[i].p * sum(lower_bound(b + 1, b + b[0] + 1, q[i].z) - b);
        ans[q[i].id] -= q[i].p * sum(lower_bound(b + 1, b + b[0] + 1, q[i].y) - b);
    }
    m >>= 1;
    for (int i = 0; i < m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
