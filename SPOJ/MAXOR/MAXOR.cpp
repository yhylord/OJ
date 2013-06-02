#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 12222;

int a[MAXN], b[MAXN], u[111][MAXN];

struct node {
    int s;
    node *c[2];
} nil[MAXN * 33], *root[MAXN], *tot = nil;

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

void insert(node *x, node *&y, int v, int k) {
    (y = ++tot)->s = x->s + 1;
    if (!k)
        return;
    int cur = (v >> k - 1) & 1;
    y->c[cur ^ 1] = x->c[cur ^ 1];
    insert(x->c[cur], y->c[cur], v, k - 1);
}

inline int query(node *x, node *y, int v) {
    int ret = 0;
    for (int k = 31; k; --k) {
        int cur = ((v >> k - 1) & 1) ^ 1;
        if (y->c[cur]->s - x->c[cur]->s)
            ret += 1 << k - 1, x = x->c[cur], y = y->c[cur];
        else
            x = x->c[cur ^ 1], y = y->c[cur ^ 1];
    }
    return ret;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int len = 150;
    nil->c[0] = nil->c[1] = nil;
    insert(root[0] = nil, root[1], 0, 31);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        b[i] = i / len;
        a[i] = a[i - 1] ^ x;
        insert(root[i], root[i + 1], a[i], 31);
    }
    for (int i = 0; i <= n; i += len)
        for (int j = i + 1; j <= n; ++j)
            u[b[i]][j] = max(u[b[i]][j - 1], query(root[i], root[j + 1], a[j]));
    for (int lst = 0; m--; ) {
        int x, y;
        scanf("%d%d", &x, &y);
        x = (unsigned(x) + unsigned(lst)) % n + 1;
        y = (unsigned(y) + unsigned(lst)) % n + 1;
        if (x > y)
            swap(x, y);
        lst = u[b[--x] + 1][y];
        for (int i = min((b[x] + 1) * len - 1, y); i >= x; --i)
            checkmax(lst, query(root[i], root[y + 1], a[i]));
        printf("%d\n", lst);
    }
    return 0;
}
