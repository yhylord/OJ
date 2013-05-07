#include <cstdio>

const int MAXN = 1111;

char a[MAXN], b[MAXN];

int main() {
    scanf("%s%s", a, b);
    int x = 0, y = 0;
    for (int i = 0; a[i]; ++i)
        x += a[i] == '1';
    for (int i = 0; b[i]; ++i)
        y += b[i] == '1';
    puts(x + (x & 1) >= y ? "YES" : "NO");
    return 0;
}
