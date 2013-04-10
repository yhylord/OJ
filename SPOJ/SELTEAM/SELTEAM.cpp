#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 100000, MAXK = 23;

int c[MAXN + 1][MAXK + 1];

int main() {
    c[0][0] = 1;
    for (int i = 1; i <= MAXN; ++i) {
        c[i][0] = 1;
        for (int j = 1; j <= min(i, MAXK); ++j)
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1] & (1 << 23) - 1;
    }
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, k, ans = 0;
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= min(k, MAXK); ++i)
            ans = ans + ((long long)c[n][i] * i * 1 << i - 1) & (1 << 23) - 1;
        printf("%d\n", ans);
    }
    return 0;
}
