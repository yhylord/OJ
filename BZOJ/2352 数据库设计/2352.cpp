#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 222222;

struct query {
    int op, x, y;
} q[MAXN];

int m, a[MAXN << 1], s[MAXN << 1];

inline void add(int x) {
    for (; x <= m; x += x & -x)
        ++s[x];
}

inline int sum(int x) {
    int ret = 0;
    for (; x; x -= x & -x)
        ret += s[x];
    return ret;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &q[i].op);
        if (q[i].op) {
            scanf("%d%d", &q[i].x, &q[i].y);
            a[m++] = q[i].x - 1;
            a[m++] = q[i].y;
        }
        else {
            scanf("%d", &q[i].x);
            a[m++] = q[i].x;
        }
    }
    sort(a, a + m);
    m = unique(a, a + m) - a;
    for (int i = 0; i < n; ++i)
        if (q[i].op)
            printf("%d\n", sum(lower_bound(a, a + m, q[i].y) - a + 1) - sum(lower_bound(a, a + m, q[i].x - 1) - a + 1));
        else
            add(lower_bound(a, a + m, q[i].x) - a + 1);
    return 0;
}
