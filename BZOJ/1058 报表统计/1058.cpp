#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int MAXN = 2222222, INF = 1000000000;

char op[22];
int n, s[MAXN];

struct node {
    node *l, *r;
    int k, p, sz, mx, mn, g;
} nil[MAXN], *tot = nil;

inline void add(int x) {
    for (; x <= n; x += x & -x)
        ++s[x];
}

inline int sum(int x) {
    int ret = 0;
    for (; x; x -= x & -x)
        ret += s[x];
    return ret;
}

inline void update(node *x) {
    x->sz = x->l->sz + x->r->sz + 1;
    x->mx = x->r != nil ? x->r->mx : x->k;
    x->mn = x->l != nil ? x->l->mn : x->k;
    x->g = min(x->l != nil ? min(x->l->g, abs(x->k - x->l->mx)) : INF, x->r != nil ? min(x->r->g, abs(x->k - x->r->mn)) : INF);
}

inline void zig(node *&x) {
    node *y = x->l;
    x->l = y->r, y->r = x;
    update(x), x = y;
}

inline void zag(node *&x) {
    node *y = x->r;
    x->r = y->l, y->l = x;
    update(x), x = y;
}

void insert(node *&x, int v) {
    if (x == nil) {
        (x = ++tot)->p = rand(), x->sz = 1, x->g = INF;
        x->mx = x->mn = x->k = v, x->l = x->r = nil;
        return;
    }
    if (v < x->k) {
        insert(x->l, v);
        if (x->l->p > x->p)
            zig(x);
    }
    else {
        insert(x->r, v);
        if (x->r->p > x->p)
            zag(x);
    }
    update(x);
}

void insert(node *&x, int pos, int v) {
    if (x == nil) {
        (x = ++tot)->p = rand(), x->sz = 1, x->g = INF;
        x->mx = x->mn = x->k = v, x->l = x->r = nil;
        return;
    }
    if (pos <= x->l->sz + 1) {
        insert(x->l, pos, v);
        if (x->l->p > x->p)
            zig(x);
    }
    else {
        insert(x->r, pos - x->l->sz - 1, v);
        if (x->r->p > x->p)
            zag(x);
    }
    update(x);
}

int main() {
    int m;
    node *root1 = nil, *root2 = nil;
    nil->l = nil->r = nil;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        add(i);
        insert(root1, i, x);
        if (root2 == nil || root2->g)
            insert(root2, x);
    }
    while (m--) {
        scanf("%s", op);
        if (op[4] == 'R') {
            int x, y;
            scanf("%d%d", &x, &y);
            add(x);
            insert(root1, sum(x), y);
            if (root2->g)
                insert(root2, y);
        }
        else if (op[4] == 'S')
            printf("%d\n", root2->g);
        else
            printf("%d\n", root1->g);
    }
    return 0;
}
