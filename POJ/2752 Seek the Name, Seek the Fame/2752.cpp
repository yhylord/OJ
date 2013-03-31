#include <cstdio>
#include <cstring>

const int MAXN = 444444;

char s[MAXN];
int p[MAXN], ans[MAXN];

int main() {
    while (scanf("%s", s + 1) != EOF) {
        int n = strlen(s + 1);
        for (int i = 2, j = 0; i <= n; ++i) {
            while (j && s[i] != s[j + 1])
                j = p[j];
            p[i] = j += s[i] == s[j + 1];
        }
        ans[0] = 0;
        for (int i = n; i; i = p[i])
            ans[++ans[0]] = i;
        for (int i = ans[0]; i > 1; --i)
            printf("%d ", ans[i]);
        printf("%d\n", ans[1]);
    }
    return 0;
}
