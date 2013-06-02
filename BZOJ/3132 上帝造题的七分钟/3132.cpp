#include <cstdio>

const int MAXN = 2222;

int n, m;

struct bit {
    int s[MAXN][MAXN];

    inline void add(int x, int y, int v) {
        for (; x <= n; x += x & -x)
            for (int ty = y; ty <= m; ty += ty & -ty)
                s[x][ty] += v;
    }

    inline int sum(int x, int y) {
        int ret = 0;
        for (; x; x -= x & -x)
            for (int ty = y; ty; ty -= ty & -ty)
                ret += s[x][ty];
        return ret;
    }
} b1, b2, b3, b4;

inline void update(int x, int y, int d) {
    if (!x || !y)
        return;
    b1.add(x, y, x * y * d);
    b2.add(x, 1, x * d), b2.add(x, y, -x * d);
    b3.add(1, y, y * d), b3.add(x, y, -y * d);
    b4.add(1, 1, d), b4.add(x, y, d), b4.add(x, 1, -d), b4.add(1, y, -d);
}

inline int query(int x, int y) {
    return x && y ? b1.sum(x, y) + b2.sum(x, y) * y + b3.sum(x, y) * x + b4.sum(x, y) * x * y : 0;
}

int main() {
    char op;
    int x1, y1, x2, y2, d;
    scanf(" %*c%d%d", &n, &m);
    while (scanf(" %c%d%d%d%d", &op, &x1, &y1, &x2, &y2) != EOF)
        if (op == 'L') {
            scanf("%d", &d);
            update(x2, y2, d), update(x1 - 1, y1 - 1, d);
            update(x2, y1 - 1, -d), update(x1 - 1, y2, -d);
        }
        else
            printf("%d\n", query(x2, y2) + query(x1 - 1, y1 - 1) - query(x2, y1 - 1) - query(x1 - 1, y2));
    return 0;
}
