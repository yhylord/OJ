#include <cstdio>

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    if (n < 3 * k) {
        puts("-1");
        return 0;
    }
    printf("1 1");
    for (int i = 2; i <= k; ++i)
        printf(" %d %d", i, i);
    for (int i = 1; i <= k; ++i)
        printf(" %d", i);
    for (int i = 3 * k + 1; i <= n; ++i)
        printf(" 1");
    puts("");
    return 0;
}
