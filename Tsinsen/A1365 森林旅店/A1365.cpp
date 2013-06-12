#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef long long LL;

const int MAXN = 122222;

int d, k, m;

struct point {
    int x[2];
} p[MAXN], q;

struct node {
    int mx[2], mn[2];
    node *l, *r;
    point p;
} nil[MAXN], *root, *tot = nil;

struct answer {
    LL a[3];

    inline void clear() {
        a[0] = a[1] = a[2] = LONG_LONG_MAX;
    }

    inline void update(LL d) {
        for (int i = 0; i < m; ++i)
            if (d < a[i]) {
                for (int j = m - 1; j > i; --j)
                    a[j] = a[j - 1];
                a[i] = d;
                break;
            }
    }
} ans;

inline bool operator <(const point &a, const point &b) {
    return a.x[d] < b.x[d];
}

inline LL sqr(LL x) {
    return x * x;
}

inline LL dist(const point &a, const point &b) {
    return k == 1 ? abs(a.x[0] - b.x[0]) + abs(a.x[1] - b.x[1]) : sqr(a.x[0] - b.x[0]) + sqr(a.x[1] - b.x[1]);
}

void build(node *&x, int f, int t, int dep) {
    if (f > t) {
        x = nil;
        return;
    }
    d = dep;
    int mid = f + t >> 1;
    nth_element(p + f, p + mid, p + t + 1);
    (x = ++tot)->p = p[mid];
    build(x->l, f, mid - 1, dep ^ 1);
    build(x->r, mid + 1, t, dep ^ 1);
    for (int u = 0; u < 2; ++u) {
        x->mx[u] = max(x->p.x[u], max(x->l->mx[u], x->r->mx[u]));
        x->mn[u] = min(x->p.x[u], min(x->l->mn[u], x->r->mn[u]));
    }
}

void insert(node *&x, int dep) {
    if (x == nil) {
        (x = ++tot)->p = q;
        x->l = x->r = nil;
    }
    else {
        d = dep;
        insert(q < x->p ? x->l : x->r, dep ^ 1);
    }
    for (int u = 0; u < 2; ++u) {
        x->mx[u] = max(x->p.x[u], max(x->l->mx[u], x->r->mx[u]));
        x->mn[u] = min(x->p.x[u], min(x->l->mn[u], x->r->mn[u]));
    }
}

void query(node *x, int dep) {
    d = dep;
    ans.update(dist(q, x->p));
    if (q < x->p) {
        if (x->l != nil)
            query(x->l, dep ^ 1);
        d = dep;
        if (x->r != nil) {
            int td = x->r->mn[d ^ 1] > q.x[d ^ 1] ? x->r->mn[d ^ 1] - q.x[d ^ 1] : q.x[d ^ 1] > x->r->mx[d ^ 1] ? q.x[d ^ 1] - x->r->mx[d ^ 1] : 0;
            if ((k == 1 ? x->r->mn[d] - q.x[d] + td : sqr(x->r->mn[d] - q.x[d]) + sqr(td)) < ans.a[m - 1])
                query(x->r, dep ^ 1);
        }
    }
    else {
        if (x->r != nil)
            query(x->r, dep ^ 1);
        d = dep;
        if (x->l != nil) {
            int td = x->l->mn[d ^ 1] > q.x[d ^ 1] ? x->l->mn[d ^ 1] - q.x[d ^ 1] : q.x[d ^ 1] > x->l->mx[d ^ 1] ? q.x[d ^ 1] - x->l->mx[d ^ 1] : 0;
            if ((k == 1 ? q.x[d] - x->l->mx[d] + td : sqr(q.x[d] - x->l->mx[d]) + sqr(td)) < ans.a[m - 1])
                query(x->l, dep ^ 1);
        }
    }
}

int main() {
    int n, t;
    scanf("%d%d%d%d", &n, &t, &k, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &p[i].x[0], &p[i].x[1]);
    nil->mx[0] = nil->mx[1] = 0;
    nil->mn[0] = nil->mn[1] = INT_MAX;
    build(root, 1, n, 0);
    while (t--) {
        char op;
        scanf(" %c%d%d", &op, &q.x[0], &q.x[1]);
        if (op == 'Q') {
            ans.clear();
            query(root, 0);
            for (int i = 0; i < m; ++i)
                printf(i == m - 1 ? "%.4lf\n" : "%.4lf ", k == 1 ? ans.a[i] : sqrt(ans.a[i]));
        }
        else
            insert(root, 0);
    }
    return 0;
}
