#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int MAXN = 222222;

int f[MAXN], s[MAXN], c[MAXN], d[MAXN], k[MAXN], p[MAXN], l[MAXN], r[MAXN], tot;

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

inline void update(int x) {
    c[x] = c[l[x]] + c[r[x]] + d[x];
}

inline void zig(int &x) {
    int y = l[x];
    l[x] = r[y];
    r[y] = x;
    update(x);
    x = y;
}

inline void zag(int &x) {
    int y = r[x];
    r[x] = l[y];
    l[y] = x;
    update(x);
    x = y;
}

void insert(int &x, int v) {
    if (!x) {
        k[x = ++tot] = v;
        c[x] = d[x] = 1;
        p[x] = rand();
        return;
    }
    if (v == k[x])
        ++d[x];
    else if (v < k[x]) {
        insert(l[x], v);
        if (p[l[x]] < p[x])
            zig(x);
    }
    else {
        insert(r[x], v);
        if (p[r[x]] < p[x])
            zag(x);
    }
    update(x);
}

void erase(int x, int v) {
    if (v == k[x])
        --d[x];
    else
        erase(v < k[x] ? l[x] : r[x], v);
    update(x);
}

int select(int x, int v) {
    return v <= c[r[x]] ? select(r[x], v) : v > c[r[x]] + d[x] ? select(l[x], v - c[r[x]] - d[x]) : k[x];
}

int main() {
    srand(0);
    int n, m, root = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        f[i] = i;
        insert(root, s[i] = 1);
    }
    while (m--) {
        int op, i, j, k;
        scanf("%d", &op);
        if (!op) {
            scanf("%d%d", &i, &j);
            int x = find(i), y = find(j);
            if (x != y) {
                erase(root, s[x]);
                erase(root, s[y]);
                if (s[x] < s[y])
                    swap(x, y);
                f[y] = x;
                insert(root, s[x] += s[y]);
            }
        }
        else {
            scanf("%d", &k);
            printf("%d\n", select(root, k));
        }
    }
    return 0;
}
