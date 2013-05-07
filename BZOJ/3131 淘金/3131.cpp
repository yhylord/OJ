#include <algorithm>
#include <cstdio>
#include <map>
#include <queue>

using namespace std;

typedef long long LL;
typedef pair<LL, int> PLI;

const int MAXN = 22222, MAXL = 22, MOD = 1000000007;

int b[MAXL], p[MAXN];
LL a[MAXN], s[MAXN];
map<LL, int> f[2][2][MAXL];
priority_queue<PLI> q;

int calc(bool less, bool first, int dep, LL pro) {
    int t = f[less][first][dep][pro];
    if (t)
        return t == -1 ? 0 : t;
    if (!dep)
        return !first && pro == 1;
    t = first ? calc(1, 1, dep - 1, pro) : 0;
    int mx = less ? 9 : b[dep];
    for (int i = 1; i <= mx; ++i)
        if (pro % i == 0)
            t += calc(less || i < b[dep], 0, dep - 1, pro / i);
    if (t)
        return f[less][first][dep][pro] = t;
    f[less][first][dep][pro] = -1;
    return 0;
}

bool cmp(int x, int y) {
    return x > y;
}

int main() {
    LL n;
    int k;
    scanf("%lld%d", &n, &k);
    for (LL i = 1; i <= n; i *= 2)
        for (LL j = i; j <= n; j *= 3)
            for (LL k = j; k <= n; k *= 5)
                for (LL l = k; l <= n; l *= 7)
                    a[++a[0]] = l;
    for (; n; n /= 10)
        b[++b[0]] = n % 10;
    for (int i = 1; i <= a[0]; ++i)
        s[i] = calc(0, 1, b[0], a[i]);
    sort(s + 1, s + a[0] + 1, cmp);
    for (int i = 1; i <= a[0]; ++i)
        q.push(make_pair(s[i] * s[p[i] = 1], i));
    int ans = 0;
    while (k-- && !q.empty()) {
        PLI cur = q.top();
        q.pop();
        (ans += cur.first % MOD) %= MOD;
        if (p[cur.second] < a[0])
            q.push(make_pair(s[cur.second] * s[++p[cur.second]], cur.second));
    }
    printf("%d\n", ans);
    return 0;
}
