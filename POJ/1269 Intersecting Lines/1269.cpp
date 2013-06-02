#include <cstdio>

struct point {
    int x, y;

    inline point(int x = 0, int y = 0): x(x), y(y) {}
} a, b, c, d;

inline point operator -(point a, point b) {
    return point(a.x - b.x, a.y - b.y);
}

inline point operator *(point a, int b) {
    return point(a.x * b, a.y * b);
}

inline int det(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

inline void intersection(point a, point b, point c, point d) {
    int s1 = det(c - a, b - a), s2 = det(d - a, b - a);
    if (s1 == s2)
        puts(s1 ? "NONE" : "LINE");
    else {
        point t = c * s2 - d * s1;
        printf("POINT %.2f %.2f\n", t.x / double(s2 - s1), t.y / double(s2 - s1));
    }
}

int main() {
    puts("INTERSECTING LINES OUTPUT");
    int n;
    scanf("%d", &n);
    while (n--) {
        scanf("%d%d%d%d%d%d%d%d", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &d.x, &d.y);
        intersection(a, b, c, d);
    }
    puts("END OF OUTPUT");
    return 0;
}
