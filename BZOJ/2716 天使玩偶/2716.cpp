#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int MAXN = 511111, INF = 100000000;

int d, ans;

struct point {
    int x[2], mk;

    inline void init(int b) {
        mk = b;
        scanf("%d%d", &x[0], &x[1]);
    }
} p[MAXN << 1], w[MAXN], q;

struct node {
    int mx[2], mn[2];
    node *l, *r, *f;
    point p;

    inline void update() {
        for (int i = 0; i < 2; ++i) {
            mx[i] = max(p.mk ? -INF : p.x[i], max(l->mx[i], r->mx[i]));
            mn[i] = min(p.mk ? INF : p.x[i], min(l->mn[i], r->mn[i]));
        }
    }
} nil[MAXN << 1], *pos[MAXN], *root, *tot = nil;

inline bool operator <(const point &a, const point &b) {
    return a.x[d] < b.x[d];
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
    pos[x->p.mk] = x;
    build(x->l, f, mid - 1, dep ^ 1);
    x->l->f = x;
    build(x->r, mid + 1, t, dep ^ 1);
    x->r->f = x;
    x->update();
}

void query(node *x, int dep) {
    d = dep;
    if (!x->p.mk)
        ans = min(ans, abs(x->p.x[0] - q.x[0]) + abs(x->p.x[1] - q.x[1]));
    if (q < x->p) {
        if (x->l != nil)
            query(x->l, dep ^ 1);
        d = dep ^ 1;
        if (x->r != nil && x->r->mn[d ^ 1] - q.x[d ^ 1] + (x->r->mn[d] > q.x[d] ? x->r->mn[d] - q.x[d] : q.x[d] > x->r->mx[d] ? q.x[d] - x->r->mx[d] : 0) < ans)
            query(x->r, dep ^ 1);
    }
    else {
        if (x->r != nil)
            query(x->r, dep ^ 1);
        d = dep ^ 1;
        if (x->l != nil && q.x[d ^ 1] - x->l->mx[d ^ 1] + (x->l->mn[d] > q.x[d] ? x->l->mn[d] - q.x[d] : q.x[d] > x->l->mx[d] ? q.x[d] - x->l->mx[d] : 0) < ans)
            query(x->l, dep ^ 1);
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        p[i].init(0);
    int cnt = n;
    for (int i = 1; i <= m; ++i) {
        int x;
        scanf("%d", &x);
        w[i].init(x == 2);
        if (!w[i].mk) {
            p[++cnt] = w[i];
            p[cnt].mk = i;
        }
    }
    nil->mx[0] = nil->mx[1] = -INF;
    nil->mn[0] = nil->mn[1] = INF;
    build(root, 1, cnt, 0);
    for (int i = 1; i <= m; ++i)
        if (w[i].mk) {
            q = w[i];
            ans = INF;
            query(root, 0);
            printf("%d\n", ans);
        }
        else {
            node *x = pos[i];
            x->p.mk = 0;
            for (; x != root; x = x->f)
                x->update();
            root->update();
        }
    return 0;
}
