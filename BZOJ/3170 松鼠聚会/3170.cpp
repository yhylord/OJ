#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long LL;

const int MAXN = 222222;

int a[MAXN], b[MAXN], c[MAXN], x[MAXN], y[MAXN], cnt[MAXN];
LL dist[MAXN], sum[MAXN];

int main() {
    int n, m = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        a[i] = x + y, b[i] = x - y;
        c[++m] = a[i], c[++m] = b[i];
    }
    sort(c + 1, c + m + 1);
    m = unique(c + 1, c + m + 1) - c - 1;
    for (int i = 0; i < n; ++i) {
        x[i] = lower_bound(c + 1, c + m + 1, a[i]) - c;
        ++cnt[x[i]];
        sum[x[i]] += a[i];
    }
    for (int i = 1; i <= m; ++i) {
        cnt[i] += cnt[i - 1];
        sum[i] += sum[i - 1];
    }
    for (int i = 0; i < n; ++i)
        dist[i] += LL(cnt[x[i] - 1]) * a[i] - sum[x[i] - 1] + sum[m] - sum[x[i]] - LL(cnt[m] - cnt[x[i]]) * a[i];
    memset(cnt, 0, sizeof cnt);
    memset(sum, 0, sizeof sum);
    for (int i = 0; i < n; ++i) {
        y[i] = lower_bound(c + 1, c + m + 1, b[i]) - c;
        ++cnt[y[i]];
        sum[y[i]] += b[i];
    }
    for (int i = 1; i <= m; ++i) {
        cnt[i] += cnt[i - 1];
        sum[i] += sum[i - 1];
    }
    for (int i = 0; i < n; ++i)
        dist[i] += LL(cnt[y[i] - 1]) * b[i] - sum[y[i] - 1] + sum[m] - sum[y[i]] - LL(cnt[m] - cnt[y[i]]) * b[i];
    LL ans = LONG_LONG_MAX;
    for (int i = 0; i < n; ++i)
        if (dist[i] < ans)
            ans = dist[i];
    printf("%lld\n", ans >> 1);
    return 0;
}
