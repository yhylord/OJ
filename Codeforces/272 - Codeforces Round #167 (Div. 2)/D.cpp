#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 222222;

pair<int, int> a[MAXN];

int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i].first);
        a[i].second = i;
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i + n].first);
        a[i + n].second = i;
    }
    scanf("%d", &m);
    n <<= 1;
    sort(a + 1, a + n + 1);
    long long ans = 1;
    for (int i = 1; i <= n; )
        if (a[i].first != a[i - 1].first) {
            int j = i + 1, t = 0;
            for (; a[j].first == a[i].first; ++j)
                if (a[j].second == a[j - 1].second)
                    ++t;
            int k = j - i;
            for (; k; --k) {
                int c = k;
                if (t && c % 2 == 0) {
                    --t;
                    c >>= 1;
                }
                (ans *= c) %= m;
            }
            i = j;
        }
    printf("%I64d\n", ans);
    return 0;
}
