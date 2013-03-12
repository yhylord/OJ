#include <cstdio>

const int MAXN = 222222, MOD = 10007;

char s[MAXN];
int f[MAXN], p[MAXN];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d ", &n);
        gets(s + 1);
        int ans = f[1] = 1;
        for (int i = 2, j = 0; i <= n; ++i) {
            while (j && s[i] != s[j + 1])
                j = p[j];
            p[i] = j += s[i] == s[j + 1];
            (ans += f[i] = f[p[i]] + 1) %= MOD;
        }
        printf("%d\n", ans);
    }
    return 0;
}
