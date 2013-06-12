#include <algorithm>
#include <climits>
#include <cstdio>

using namespace std;

#define lc x << 1
#define rc (lc) + 1

typedef long long LL;
typedef pair<LL, int> PLI;

const int MAXN = 111111;

int d, num;

struct point {
    int x[2], id;
} p[MAXN], q;

struct node {
    point p;
    int mx[2], mn[2];
} a[MAXN << 1];

struct answer {
    PLI a[22];

    inline void clear() {
        for (int i = 0; i < num; ++i)
            a[i] = make_pair(LONG_LONG_MAX, INT_MAX);
    }

    inline void update(PLI x) {
        for (int i = 0; i < num; ++i)
            if (x < a[i]) {
                for (int j = num - 1; j > i; --j)
                    a[j] = a[j - 1];
                a[i] = x;
                break;
            }
    }
} ans;

inline bool operator <(const point &a, const point &b) {
    return a.x[d] < b.x[d];
}

inline LL dist(LL x, LL y) {
    return x * x + y * y;
}

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

inline void checkmin(int &x, int y) {
    if (y < x)
        x = y;
}

void build(int x, int f, int t, int dep) {
    d = dep;
    int mid = f + t >> 1;
    nth_element(p + f, p + mid, p + t + 1);
    a[x].p = p[mid];
    for (int u = 0; u < 2; ++u)
        a[x].mx[u] = a[x].mn[u] = a[x].p.x[u];
    if (f < mid) {
        build(lc, f, mid - 1, dep ^ 1);
        for (int u = 0; u < 2; ++u)
            checkmax(a[x].mx[u], a[lc].mx[u]), checkmin(a[x].mn[u], a[lc].mn[u]);
    }
    if (t > mid) {
        build(rc, mid + 1, t, dep ^ 1);
        for (int u = 0; u < 2; ++u)
            checkmax(a[x].mx[u], a[rc].mx[u]), checkmin(a[x].mn[u], a[rc].mn[u]);
    }
}

void query(int x, int f, int t, int dep) {
    d = dep;
    ans.update(make_pair(-dist(q.x[0] - a[x].p.x[0], q.x[1] - a[x].p.x[1]), a[x].p.id));
    if (f == t)
        return;
    int mid = f + t >> 1;
    if (q < a[x].p) {
        if (t > mid)
            query(rc, mid + 1, t, dep ^ 1);
        if (f < mid && -dist(max(a[lc].mx[0] - q.x[0], q.x[0] - a[lc].mn[0]), max(a[lc].mx[1] - q.x[1], q.x[1] - a[lc].mn[1])) <= ans.a[num - 1].first)
            query(lc, f, mid - 1, dep ^ 1);
    }
    else {
        if (f < mid)
            query(lc, f, mid - 1, dep ^ 1);
        if (t > mid && -dist(max(a[rc].mx[0] - q.x[0], q.x[0] - a[rc].mn[0]), max(a[rc].mx[1] - q.x[1], q.x[1] - a[rc].mn[1])) <= ans.a[num - 1].first)
            query(rc, mid + 1, t, dep ^ 1);
    }
}

int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &p[p[i].id = i].x[0], &p[i].x[1]);
    build(1, 1, n, 0);
    scanf("%d", &m);
    while (m--) {
        scanf("%d%d%d", &q.x[0], &q.x[1], &num);
        ans.clear();
        query(1, 1, n, 0);
        printf("%d\n", ans.a[num - 1].second);
    }
    return 0;
}
