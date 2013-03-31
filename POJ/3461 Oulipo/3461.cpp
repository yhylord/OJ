#include <cstdio>
#include <cstring>

const int MAXN = 1111111;

char a[MAXN], b[MAXN];
int p[MAXN];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s%s", a + 1, b + 1);
        int n = strlen(a + 1), m = strlen(b + 1), ans = 0;
        for (int i = 2, j = 0; i <= n; ++i) {
            while (j && a[i] != a[j + 1])
                j = p[j];
            p[i] = j += a[i] == a[j + 1];
        }
        for (int i = 1, j = 0; i <= m; ++i) {
            while (j && b[i] != a[j + 1])
                j = p[j];
            ans += (j += b[i] == a[j + 1]) == n;
        }
        printf("%d\n", ans);
    }
    return 0;
}
