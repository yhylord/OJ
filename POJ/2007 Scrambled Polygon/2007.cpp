#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 55;

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

inline bool operator <(const point &a, const point &b) {
    return det(a - p[0], b - p[0]) > 0;
}

int main() {
    int n = 0, c;
    for (; scanf("%d%d", &p[n].x, &p[n].y) != EOF; ++n)
        if (p[n].y < p[0].y || p[n].y == p[0].y && p[n].x < p[0].x)
            swap(p[n], p[0]);
    sort(p + 1, p + n);
    for (int i = 0; i < n; ++i)
        if (!p[i].x && !p[i].y)
            c = i;
    for (int i = c; i < n; ++i)
        printf("(%d,%d)\n", p[i].x, p[i].y);
    for (int i = 0; i < c; ++i)
        printf("(%d,%d)\n", p[i].x, p[i].y);
    return 0;
}
