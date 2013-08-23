#include <algorithm>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int MAXN = 111111;

int cnt, a[MAXN], s[MAXN];
pair<int, int> b[MAXN];

inline void add(int x, int v) {
    for (; x <= cnt; x += x & -x)
        s[x] += v;
}

inline int sum(int x) {
    int ret = 0;
    for (; x; x -= x & -x)
        ret += s[x];
    return ret;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    cnt = n + m;
    for (int i = n; i; --i) {
        scanf("%d", &a[i]);
        add(i, 1);
        b[i] = make_pair(-a[i], i);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &a[n + i]);
        add(n + i, 1);
        b[n + i] = make_pair(-a[n + i], n + i);
    }
    int cur = n;
    long long ans = 0;
    sort(b + 1, b + cnt + 1);
    for (int i = 1; i <= cnt; ++i) {
        ans += abs(sum(b[i].second) - sum(cur)) - (b[i].second > cur);
        add(cur = b[i].second, -1);
    }
    printf("%lld\n", ans);
    return 0;
}
