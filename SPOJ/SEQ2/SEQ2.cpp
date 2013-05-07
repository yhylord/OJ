#include <algorithm>
#include <climits>
#include <cstdio>

using namespace std;

const int MAXN = 4444444;

char op[11];
int a[MAXN];

struct node {
    bool rev, e, u;
    int v, d, l, r, m, sz;
    node *s[2], *p;

    inline int dir() {
        return this == p->s[1];
    }

    inline void sets(node *x, int dir) {
        (s[dir] = x)->p = this;
    }

    inline void cover(int c) {
        if (sz) {
            u = true;
            d = sz * (v = c);
            l = r = m = c >= 0 ? d : c;
        }
    }

    inline void reverse() {
        if (sz) {
            rev ^= 1;
            swap(s[0], s[1]);
            swap(l, r);
        }
    }

    inline void push() {
        if (rev) {
            rev = false;
            s[0]->reverse();
            s[1]->reverse();
        }
        if (u) {
            u = false;
            s[0]->cover(v);
            s[1]->cover(v);
        }
    }

    inline void update() {
        sz = s[0]->sz + s[1]->sz + 1;
        d = s[0]->d + s[1]->d + v;
        l = max(s[0]->l, s[0]->d + v + max(s[1]->l, 0));
        r = max(s[1]->r, s[1]->d + v + max(s[0]->r, 0));
        m = max(max(s[0]->m, s[1]->m), e ? INT_MIN : max(s[0]->r, 0) + v + max(s[1]->l, 0));
    }
} nil[MAXN], *root, *tot;

inline void rotate(node *x) {
    int d = x->dir();
    node *p = x->p;
    if (p->p != nil)
        p->p->sets(x, p->dir());
    else
        x->p = p->p;
    p->sets(x->s[!d], d);
    x->sets(p, !d);
    p->update();
}

inline void splay(node *x, node *y) {
    while (x->p != y)
        if (x->p->p == y)
            rotate(x);
        else if (x->p->dir() == x->dir())
            rotate(x->p), rotate(x);
        else
            rotate(x), rotate(x);
    x->update();
    if (y == nil)
        root = x;
}

node *build(int l, int r) {
    node *x = ++tot;
    int mid = l + r >> 1;
    x->v = a[mid];
    x->s[0] = x->s[1] = nil;
    x->rev = x->u = false;
    if (l <= mid - 1)
        x->sets(build(l, mid - 1), 0);
    if (mid + 1 <= r)
        x->sets(build(mid + 1, r), 1);
    x->update();
    return x;
}

inline node *select(int k) {
    node *x = root;
    for (x->push(); x->s[0]->sz + 1 != k; x->push())
        if (k <= x->s[0]->sz)
            x = x->s[0];
        else
            k -= x->s[0]->sz + 1, x = x->s[1];
    return x;
}

inline void work() {
    int n, m;
    scanf("%d%d", &n, &m);
    root = nil + 1, tot = nil + 2;
    nil->l = nil->r = nil->m = INT_MIN;
    nil->s[0] = nil->s[1] = nil->p = root->s[0] = root->p = tot->s[0] = tot->s[1] = nil;
    root->v = root->d = root->l = root->r = root->m = tot->v = tot->d = tot->l = tot->r = tot->m = 0;
    root->rev = root->u = tot->rev = tot->u = false;
    root->e = tot->e = true;
    root->sets(tot, 1);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    root->s[1]->sets(build(1, n), 0);
    root->s[1]->update();
    root->update();
    while (m--) {
        int p, tot;
        scanf("%s", op);
        if (op[2] == 'S') {
            scanf("%d%d", &p, &tot);
            for (int i = 1; i <= tot; ++i)
                scanf("%d", &a[i]);
            splay(select(p + 1), nil);
            splay(select(p + 2), root);
            root->s[1]->sets(build(1, tot), 0);
            root->s[1]->update();
            root->update();
        }
        else if (op[2] == 'L') {
            scanf("%d%d", &p, &tot);
            splay(select(p), nil);
            splay(select(p + tot + 1), root);
            root->s[1]->s[0] = nil;
            root->s[1]->update();
            root->update();
        }
        else if (op[2] == 'K') {
            int c;
            scanf("%d%d%d", &p, &tot, &c);
            splay(select(p), nil);
            splay(select(p + tot + 1), root);
            root->s[1]->s[0]->cover(c);
            root->s[1]->update();
            root->update();
        }
        else if (op[2] == 'V') {
            scanf("%d%d", &p, &tot);
            splay(select(p), nil);
            splay(select(p + tot + 1), root);
            root->s[1]->s[0]->reverse();
            root->s[1]->update();
            root->update();
        }
        else if (op[2] == 'T') {
            scanf("%d%d", &p, &tot);
            splay(select(p), nil);
            splay(select(p + tot + 1), root);
            printf("%d\n", root->s[1]->s[0]->d);
        }
        else
            printf("%d\n", root->m);
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--)
        work();
    return 0;
}
