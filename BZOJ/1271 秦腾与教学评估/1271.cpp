#include <algorithm>
#include <climits>
#include <cstdio>

using namespace std;

typedef long long LL;

const int MAXN = 222222;

int s[MAXN], e[MAXN], d[MAXN];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%d%d%d", &s[i], &e[i], &d[i]);
        LL l = -1, r = INT_MAX + 1LL;
        while (l + 1 < r) {
            LL mid = l + r >> 1, cnt = 0;
            for (int i = 0; i < n; ++i) {
                int t = min(mid, LL(e[i]));
                if (t >= s[i])
                    cnt += (t - s[i]) / d[i] + 1;
            }
            if (cnt & 1)
                r = mid;
            else
                l = mid;
        }
        if (r == INT_MAX + 1LL)
            puts("Poor QIN Teng:(");
        else {
            LL cnt = 0;
            for (int i = 0; i < n; ++i)
                if (r >= s[i] && r <= e[i] && (r - s[i]) % d[i] == 0)
                    ++cnt;
            printf("%lld %lld\n", r, cnt);
        }
    }
    return 0;
}
