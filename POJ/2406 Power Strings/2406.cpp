#include <cstdio>
#include <cstring>

const int MAXN = 1111111;

char s[MAXN];
int p[MAXN];

int main() {
    while (gets(s + 1) && strcmp(s + 1, ".")) {
        int n = strlen(s + 1);
        for (int i = 2, j = 0; i <= n; ++i) {
            while (j && s[i] != s[j + 1])
                j = p[j];
            p[i] = j += s[i] == s[j + 1];
        }
        printf("%d\n", n % (n - p[n]) ? 1 : n / (n - p[n]));
    }
    return 0;
}
