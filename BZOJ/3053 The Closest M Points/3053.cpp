#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define lc x << 1
#define rc (lc) + 1

const int MAXN = 55555;

int d, k, m;

struct point {
    int x[5];

    inline void init() {
        for (int i = 0; i < k; ++i)
            scanf("%d", &x[i]);
    }

    inline void print() {
        for (int i = 0; i < k - 1; ++i)
            printf("%d ", x[i]);
        printf("%d\n", x[k - 1]);
    }
} p[MAXN], a[MAXN << 1], q;

struct answer {
    int a[10];
    point p[10];

    inline void clear() {
        for (int i = 0; i < m; ++i)
            a[i] = 1000000000;
    }

    inline void update(const point &x, const int &d) {
        for (int i = 0; i < m; ++i)
            if (d < a[i]) {
                for (int j = m - 1; j > i; --j)
                    a[j] = a[j - 1], p[j] = p[j - 1];
                a[i] = d, p[i] = x;
                break;
            }
    }
} ans;

inline bool operator <(const point &a, const point &b) {
    return a.x[d] < b.x[d];
}

inline int sqr(int x) {
    return x * x;
}

inline int dist(const point &a, const point &b) {
    int ret = 0;
    for (int i = 0; i < k; ++i)
        ret += sqr(a.x[i] - b.x[i]);
    return ret;
}

void build(int x, int f, int t, int dep) {
    d = dep % k;
    int mid = f + t >> 1;
    nth_element(p + f, p + mid, p + t + 1);
    a[x] = p[mid];
    if (f < mid)
        build(lc, f, mid - 1, dep + 1);
    if (t > mid)
        build(rc, mid + 1, t, dep + 1);
}

void query(int x, int f, int t, int dep) {
    d = dep % k;
    ans.update(a[x], dist(q, a[x]));
    int mid = f + t >> 1;
    if (q < a[x]) {
        if (f < mid)
            query(lc, f, mid - 1, dep + 1);
        d = dep % k;
        if (t > mid && sqr(q.x[d] - a[x].x[d]) < ans.a[m - 1])
            query(rc, mid + 1, t, dep + 1);
    }
    else {
        if (t > mid)
            query(rc, mid + 1, t, dep + 1);
        d = dep % k;
        if (f < mid && sqr(q.x[d] - a[x].x[d]) < ans.a[m - 1])
            query(lc, f, mid - 1, dep + 1);
    }
}

int main() {
    int n, t;
    while (scanf("%d%d", &n, &k) != EOF) {
        for (int i = 1; i <= n; ++i)
            p[i].init();
        build(1, 1, n, 0);
        scanf("%d", &t);
        while (t--) {
            q.init();
            scanf("%d", &m);
            ans.clear();
            query(1, 1, n, 0);
            printf("the closest %d points are:\n", m);
            for (int i = 0; i < m; ++i)
                ans.p[i].print();
        }
    }
    return 0;
}
