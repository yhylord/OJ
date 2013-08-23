#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 11111;

int a[MAXN], b[MAXN], ans[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &b[i]);
    for (int i = 1; i <= n; ++i) {
        double x = 1e10, y = 0;
        for (int j = 1; j <= n; ++j)
            if (i != j)
                if (a[j] <= a[i] && b[j] > b[i])
                    x = min(x, double(a[i] - a[j]) / (b[j] - b[i]));
                else if (a[j] > a[i]) {
                    if (b[j] >= b[i]) {
                        y = 1e11;
                        break;
                    }
                    y = max(y, double(a[j] - a[i]) / (b[i] - b[j]));
                }
        if (x >= y)
            ans[++ans[0]] = i;
    }
    printf("%d\n", ans[0]);
    for (int i = 1; i < ans[0]; ++i)
        printf("%d ", ans[i]);
    printf("%d\n", ans[ans[0]]);
    return 0;
}
