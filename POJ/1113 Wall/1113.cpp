#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

const int MAXN = 5555;

int s[MAXN];

struct point {
    int x, y;

    inline point(int _x = 0, int _y = 0): x(_x), y(_y) {}
} p[MAXN];

inline point operator -(const point &a, const point &b) {
    return point(a.x - b.x, a.y - b.y);
}

inline int det(const point &a, const point &b) {
    return a.x * b.y - a.y * b.x;
}

inline double sqr(double x) {
    return x * x;
}

inline double dist(const point &a, const point &b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

inline bool operator <(const point &a, const point &b) {
    int t = det(a - p[0], b - p[0]);
    return t > 0 || t == 0 && dist(p[0], a) < dist(p[0], b);
}

int main() {
    int n, l, top = 1;
    scanf("%d%d", &n, &l);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &p[i].x, &p[i].y);
        if (p[i].y < p[0].y || p[i].y == p[0].y && p[i].x < p[0].x)
            swap(p[i], p[0]);
    }
    sort(p + 1, p + n);
    s[0] = 0, s[1] = 1;
    for (int i = 2; i < n; ++i) {
        for (; top && det(p[s[top]] - p[s[top - 1]], p[i] - p[s[top]]) <= 0; --top);
        s[++top] = i;
    }
    double ans = 3.14159 * 2 * l + dist(p[s[top]], p[s[0]]);
    for (int i = 1; i <= top; ++i)
        ans += dist(p[s[i]], p[s[i - 1]]);
    printf("%.0f\n", ans);
    return 0;
}
