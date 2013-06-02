#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 333;

int a[MAXN];

int main() {
    int n, k, ans = 0;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < k; ++i)
        scanf("%d", &a[i]);
    sort(a, a + k);
    for (int i = k - 1, j = 1; i >= 0 && n - j > 0; --i, j += 2)
        ans += a[i] * (n - j);
    printf("%d\n", ans);
    return 0;
}
