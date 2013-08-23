#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int MAXN = 11111;

int s[MAXN];

struct point {
    int x, y;

    inline point(int _x = 0, int _y = 0): x(_x), y(_y) {}
} p[MAXN];

inline point operator -(const point &a, const point &b) {
    return point(a.x - b.x, a.y - b.y);
}

inline int det(const point &a, const point &b) {
    return a.x * b.y - b.x * a.y;
}

inline bool operator <(const point &a, const point &b) {
    int t = det(a - p[0], b - p[0]);
    return t > 0 || t == 0 && abs(a.x - p[0].x) < abs(b.x - p[0].x);
}

int main() {
    int n, top = s[1] = 1, area = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &p[i].x, &p[i].y);
        if (p[i].y < p[0].y || p[i].y == p[0].y && p[i].x < p[0].x)
            swap(p[i], p[0]);
    }
    sort(p + 1, p + n);
    for (int i = 2; i < n; ++i) {
        for (; top && det(p[s[top]] - p[s[top - 1]], p[i] - p[s[top]]) <= 0; --top);
        s[++top] = i;
    }
    for (int i = 2; i <= top; ++i)
        area += det(p[s[i - 1]] - p[0], p[s[i]] - p[0]);
    printf("%d\n", area / 100);
    return 0;
}
