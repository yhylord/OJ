#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

const int MAXN = 111;

double g[MAXN][MAXN];
int e[MAXN];

struct point {
    double x, y;

    inline point(double x = 0, double y = 0): x(x), y(y) {}
} p[MAXN], a[MAXN], b[MAXN];

inline point operator -(point a, point b) {
    return point(a.x - b.x, a.y - b.y);
}

inline double sqr(double x) {
    return x * x;
}

inline double dist(point a, point b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

inline double det(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

inline bool intersect(point a, point b, point c, point d) {
    return max(a.x, b.x) >= min(c.x, d.x) && max(c.x, d.x) >= min(a.x, b.x) &&
           max(a.y, b.y) >= min(c.y, d.y) && max(c.y, d.y) >= min(a.y, b.y) &&
           det(c - a, b - a) * det(d - a, b - a) <= 0 && det(a - c, d - c) * det(b - c, d - c) <= 0;
}

int main() {
    int n;
    while (scanf("%d", &n) && ~n) {
        int pcnt = 0, lcnt = 0;
        p[++pcnt] = point(0, 5);
        p[++pcnt] = point(10, 5);
        for (int i = 1; i <= n; ++i) {
            double x, y, z;
            scanf("%lf%lf", &x, &y);
            a[++lcnt] = point(x, 0);
            p[++pcnt] = b[lcnt] = point(x, y);
            e[pcnt] = lcnt;
            scanf("%lf%lf", &y, &z);
            p[++pcnt] = a[++lcnt] = point(x, y);
            e[pcnt] = lcnt;
            p[++pcnt] = b[lcnt] = point(x, z);
            e[pcnt] = lcnt;
            scanf("%lf", &y);
            p[++pcnt] = a[++lcnt] = point(x, y);
            b[lcnt] = point(x, 10);
            e[pcnt] = lcnt;
        }
        for (int i = 1; i <= pcnt; ++i)
            for (int j = 1; j <= pcnt; ++j)
                g[i][j] = 1e10;
        for (int i = 1; i <= pcnt; ++i)
            for (int j = 1; j <= pcnt; ++j)
                if (p[j].x > p[i].x) {
                    bool f = true;
                    for (int k = 1; f && k <= lcnt; ++k)
                        if (e[i] != k && e[j] != k && intersect(p[i], p[j], a[k], b[k]))
                            f = false;
                    if (f)
                        g[i][j] = dist(p[i], p[j]);
                }
        for (int k = 1; k <= pcnt; ++k)
            for (int i = 1; i <= pcnt; ++i)
                for (int j = 1; j <= pcnt; ++j)
                    if (g[i][k] + g[k][j] < g[i][j])
                        g[i][j] = g[i][k] + g[k][j];
        printf("%.2f\n", g[1][2]);
    }
    return 0;
}
