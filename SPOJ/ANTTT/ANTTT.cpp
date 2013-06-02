#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

const int MAXN = 1111;

int f[MAXN];

struct point {
    int x, y;

    inline point(int x = 0, int y = 0): x(x), y(y) {}
} a[MAXN], b[MAXN];

inline point operator -(point a, point b) {
    return point(a.x - b.x, a.y - b.y);
}

inline int det(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

inline bool intersect(point a, point b, point c, point d) {
    return max(a.x, b.x) >= min(c.x, d.x) && max(c.x, d.x) >= min(a.x, b.x) &&
           max(a.y, b.y) >= min(c.y, d.y) && max(c.y, d.y) >= min(a.y, b.y) &&
           LL(det(c - a, b - a)) * det(d - a, b - a) <= 0 && LL(det(a - c, d - c)) * det(b - c, d - c) <= 0;
}

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
            f[i] = i;
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d%d%d", &a[i].x, &a[i].y, &b[i].x, &b[i].y);
            for (int j = 1; j < i; ++j)
                if (intersect(a[i], b[i], a[j], b[j]))
                    f[find(i)] = find(j);
        }
        while (m--) {
            int x, y;
            scanf("%d%d", &x, &y);
            puts(find(x) == find(y) ? "YES" : "NO");
        }
    }
    return 0;
}
