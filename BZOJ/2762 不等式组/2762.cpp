#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 111111;

bool v[MAXN];
int m = 1, a[MAXN], id[MAXN], s[MAXN];

struct operation {
    char op[11];
    int a, b, c, d;
} q[MAXN];

inline void add(int x, int v) {
    for (; x <= m; x += x & -x)
        s[x] += v;
}

inline int sum(int x) {
    int ret = 0;
    for (; x; x -= x & -x)
        ret += s[x];
    return ret;
}

int main() {
    int n, d = 0, cnt = 0;
    scanf("%d", &n);
    a[1] = -1000000000;
    for (int i = 1; i <= n; ++i) {
        scanf("%s", q[i].op);
        if (q[i].op[0] == 'A') {
            scanf("%d%d%d", &q[i].a, &q[i].b, &q[i].c);
            int t = q[i].c - q[i].b;
            if (q[i].a > 0)
                a[++m] = q[i].d = t / q[i].a + (t >= 0 || t % q[i].a == 0);
            else if (q[i].a < 0)
                a[++m] = q[i].d = t / q[i].a + (t < 0 && t % q[i].a != 0);
        }
        else if (q[i].op[0] == 'D')
            scanf("%d", &q[i].a);
        else {
            scanf("%d", &q[i].a);
            a[++m] = q[i].a;
        }
    }
    sort(a + 1, a + m + 1);
    m = unique(a + 1, a + m + 1) - a - 1;
    for (int i = 1; i <= n; ++i)
        if (q[i].op[0] == 'A') {
            id[++cnt] = i;
            if (q[i].a > 0)
                add(lower_bound(a + 1, a + m + 1, q[i].d) - a, 1);
            else if (q[i].a < 0) {
                add(1, 1);
                add(lower_bound(a + 1, a + m + 1, q[i].d) - a, -1);
            }
            else
                d += q[i].b > q[i].c;
        }
        else if (q[i].op[0] == 'D') {
            int j = id[q[i].a];
            if (v[j])
                continue;
            v[j] = true;
            if (q[j].a > 0)
                add(lower_bound(a + 1, a + m + 1, q[j].d) - a, -1);
            else if (q[j].a < 0) {
                add(1, -1);
                add(lower_bound(a + 1, a + m + 1, q[j].d) - a, 1);
            }
            else
                d -= q[j].b > q[j].c;
        }
        else
            printf("%d\n", sum(lower_bound(a + 1, a + m + 1, q[i].a) - a) + d);
    return 0;
}
