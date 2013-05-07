#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 111111;

int a[MAXN], b[MAXN];

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    for (int i = 0; i < m; ++i)
        scanf("%d", &b[i]);
    n = max(n, m);
    sort(a, a + n);
    sort(b, b + n);
    for (int i = 0; i < n; ++i)
        if (a[i] > b[i]) {
            puts("YES");
            return 0;
        }
    puts("NO");
    return 0;
}
