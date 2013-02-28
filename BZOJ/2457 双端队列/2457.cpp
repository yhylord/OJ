#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 222222;

pair<int, int> a[MAXN];

int main() {
    int n, ans = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i].first);
        a[i].second = -i;
    }
    sort(a, a + n);
    for (int i = 0; i < n; ++i)
        a[i].second = -a[i].second;
    for (int i = 0; i < n; ) {
        ++ans;
        while (i < n) {
            for (++i; i < n && a[i].first == a[i - 1].first; ++i);
            if (a[i].second > a[i - 1].second)
                break;
        }
        int t = a[i].second;
        for (++i; i < n && a[i].first == a[i - 1].first; ++i);
        while (i < n) {
            int u = a[i].first, v = a[i].second;
            for (; i < n && a[i].first == u && a[i].second > t; ++i);
            if (a[i].second < t)
                break;
            t = v;
        }
    }
    printf("%d\n", ans);
    return 0;
}
