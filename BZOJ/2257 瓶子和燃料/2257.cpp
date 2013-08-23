#include <algorithm>
#include <cstdio>

using namespace std;

int a[2222222];

int main() {
    int n, k, m = 0;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) {
        int x, j = 1;
        scanf("%d", &x);
        for (; j * j < x; ++j)
            if (x % j == 0)
                a[m++] = j, a[m++] = x / j;
        if (j * j == x)
            a[m++] = j;
    }
    sort(a, a + m);
    for (int i = m - 1, j = 0; i >= 0; --i)
        if ((j = a[i] != a[i + 1] ? 1 : j + 1) == k) {
            printf("%d\n", a[i]);
            break;
        }
    return 0;
}
