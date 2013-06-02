#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

const int MAXN = 111111;

bool b[7], c[7];
int n, m, l, r;
LL ans;

struct data {
    int d[7];
} a[MAXN];

inline bool cmp3(const data &x, const data &y) {
    for (int i = 0; i < 6; ++i)
        if (c[i])
            if (x.d[i] < y.d[i])
                return true;
            else if (x.d[i] > y.d[i])
                return false;
    return false;
}

inline bool cmp4(const data &x, const data &y) {
    for (int i = 0; i < 6; ++i)
        if (c[i] && x.d[i] != y.d[i])
            return false;
    return true;
}

void dfs2(int dep, int sum) {
    if (dep == 6) {
        sort(a + l, a + r, cmp3);
        for (int i = l; i < r; ) {
            int j = i + 1;
            for (; j < r && cmp4(a[i], a[j]); ++j);
            if (sum & 1)
                ans -= LL(j - i) * (j - i - 1) / 2;
            else
                ans += LL(j - i) * (j - i - 1) / 2;
            i = j;
        }
        return;
    }
    if (!b[dep]) {
        c[dep] = true;
        dfs2(dep + 1, sum + 1);
    }
    c[dep] = false;
    dfs2(dep + 1, sum);
}

inline bool cmp1(const data &x, const data &y) {
    for (int i = 0; i < 6; ++i)
        if (b[i])
            if (x.d[i] < y.d[i])
                return true;
            else if (x.d[i] > y.d[i])
                return false;
    return false;
}

inline bool cmp2(const data &x, const data &y) {
    for (int i = 0; i < 6; ++i)
        if (b[i] && x.d[i] != y.d[i])
            return false;
    return true;
}

void dfs1(int dep, int sum) {
    if (dep == 6) {
        if (sum != m)
            return;
        sort(a, a + n, cmp1);
        for (int i = 0; i < n; ) {
            int j = i + 1;
            for (; j < n && cmp2(a[i], a[j]); ++j);
            l = i, r = j;
            dfs2(0, 0);
            i = j;
        }
        return;
    }
    b[dep] = true;
    dfs1(dep + 1, sum + 1);
    b[dep] = false;
    dfs1(dep + 1, sum);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < 6; ++j)
            scanf("%d", &a[i].d[j]);
    dfs1(0, 0);
    printf("%lld\n", ans);
    return 0;
}
