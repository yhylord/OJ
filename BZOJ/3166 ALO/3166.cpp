#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 55555, INF = 1000000000;

int n, tot, root[MAXN], p[MAXN * 33][2], s[MAXN * 33], d[MAXN][33],
    a[MAXN], c[MAXN], m1[MAXN], m2[MAXN], lt[MAXN], rt[MAXN];
pair<int, int> b[MAXN];

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

inline void update(int x, int v) {
    for (; x <= n; x += x & -x)
        if (v > m1[x])
            m2[x] = m1[x], m1[x] = v;
        else
            checkmax(m2[x], v);
}

inline int getmax(int x) {
    int s1 = -INF, s2 = -INF;
    for (; x; x -= x & -x) {
        if (m1[x] > s1)
            s2 = s1, s1 = m1[x];
        else
            checkmax(s2, m1[x]);
        checkmax(s2, m2[x]);
    }
    return s2;
}

void insert(int x, int &y, int no, int dep) {
    s[y = ++tot] = s[x] + 1;
    if (!dep)
        return;
    int cur = d[no][dep];
    p[y][cur ^ 1] = p[x][cur ^ 1];
    insert(p[x][cur], p[y][cur], no, dep - 1);
}

int query(int x, int y, int no, int dep) {
    if (!dep)
        return 0;
    int cur = d[no][dep] ^ 1;
    if (s[p[y][cur]] - s[p[x][cur]])
        return (1 << dep - 1) + query(p[x][cur], p[y][cur], no, dep - 1);
    return query(p[x][cur ^ 1], p[y][cur ^ 1], no, dep - 1);
}

int main() {
    int mx = 0, ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        if (a[i] > mx)
            mx = a[i];
        b[i] = make_pair(-a[i], i);
        for (int t = a[i]; t; t >>= 1)
            d[i][++d[i][0]] = t & 1;
        insert(root[i - 1], root[i], i, 30);
    }
    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; ++i) {
        c[b[i].second] = i;
        m1[i] = m2[i] = -INF;
    }
    for (int i = 1; i <= n; ++i) {
        if (a[i] != mx && (lt[i] = getmax(c[i])) == -INF)
            lt[i] = 0;
        update(c[i], i);
    }
    for (int i = 1; i <= n; ++i)
        m1[i] = m2[i] = -INF;
    for (int i = n; i; --i) {
        if (a[i] != mx && (rt[i] = -getmax(c[i])) == INF)
            rt[i] = n + 1;
        update(c[i], -i);
    }
    for (int i = 1; i <= n; ++i)
        if (a[i] != mx)
            checkmax(ans, query(root[lt[i]], root[rt[i] - 1], i, 30));
    printf("%d\n", ans);
    return 0;
}
