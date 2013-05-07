#include <cstdio>

const int MAXN = 1111;

char s[MAXN];

int main() {
    int n;
    scanf("%d%s", &n, s + 1);
    int l = 1, r = n;
    for (; s[l] == '.'; ++l);
    for (; s[r] == '.'; --r);
    if (s[l] == s[r])
        if (s[l] == 'L')
            printf("%d %d\n", r, l - 1);
        else
            printf("%d %d\n", l, r + 1);
    else {
        for (; s[l] == s[l + 1]; ++l);
        printf("%d %d\n", r, l + 1);
    }
    return 0;
}
