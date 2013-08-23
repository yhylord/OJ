#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 111;

int c[MAXN << 7], d[MAXN << 7];

struct event {
    int p, x, y1, y2, z1, z2;

    inline event() {}

    inline event(int _p, int _x, int _y1, int _y2, int _z1, int _z2): p(_p), x(_x), y1(_y1), y2(_y2), z1(_z1), z2(_z2) {}

    inline bool operator <(const event &t) const {
        return x < t.x;
    }
} a[MAXN << 1];

void cover(int x, int f, int t, int qf, int qt, int p) {
    if (qf <= f && t <= qt)
        c[x] += p;
    else {
        int mid = f + t >> 1;
        if (qf <= mid)
            cover(x << 1, f, mid, qf, qt, p);
        if (qt > mid)
            cover((x << 1) + 1, mid + 1, t, qf, qt, p);
    }
    d[x] = c[x] ? t - f + 1 : d[x << 1] + d[(x << 1) + 1];
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int x, y, z, r;
        scanf("%d%d%d%d", &x, &y, &z, &r);
        a[i] = event(-1, x - r, y - r, y + r - 1, z - r, z + r - 1);
        a[i + n] = event(1, x + r, y - r, y + r - 1, z - r, z + r - 1);
    }
    sort(a, a + (n <<= 1));
    long long ans = 0;
    for (int z = -1200; z <= 1200; ++z)
        for (int i = 0; i < n; ++i) {
            if (i && a[i].x != a[i - 1].x)
                ans += (a[i].x - a[i - 1].x) * d[1];
            if (a[i].z1 <= z && z <= a[i].z2)
                cover(1, -1200, 1200, a[i].y1, a[i].y2, a[i].p);
        }
    printf("%lld\n", ans);
    return 0;
}
