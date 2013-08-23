#include <cstdio>

const int MAXN = 666666, MAXT = 15555555;

int tot, a[MAXN], b[MAXN], root[MAXN], s[MAXT], c[MAXT][2];

void insert(int x, int &y, int v, int d) {
    s[y = ++tot] = s[x] + 1;
    if (d < 0)
        return;
    int p = (v >> d) & 1;
    c[y][p ^ 1] = c[x][p ^ 1];
    insert(c[x][p], c[y][p], v, d - 1);
}

int query(int x, int y, int v, int d) {
    if (d < 0)
        return 0;
    int p = (v >> d) & 1;
    if (s[c[y][p ^ 1]] - s[c[x][p ^ 1]])
        return (1 << d) + query(c[x][p ^ 1], c[y][p ^ 1], v, d - 1);
    return query(c[x][p], c[y][p], v, d - 1);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    ++n;
    insert(root[0], root[1], 0, 24);
    for (int i = 2; i <= n; ++i) {
        scanf("%d", &a[i]);
        insert(root[i - 1], root[i], b[i] = b[i - 1] ^ a[i], 24);
    }
    while (m--) {
        char op;
        scanf(" %c", &op);
        if (op == 'A') {
            scanf("%d", &a[++n]);
            insert(root[n - 1], root[n], b[n] = b[n - 1] ^ a[n], 24);
        }
        else {
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            printf("%d\n", query(root[l - 1], root[r], b[n] ^ x, 24));
        }
    }
    return 0;
}
