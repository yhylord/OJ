#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 222222;

char s[MAXN], a[MAXN];
int r[MAXN], c[MAXN];

int main() {
    gets(s);
    int n = 0;
    a[0] = '$';
    for (int i = 0; s[i]; ++i) {
        a[++n] = '#';
        a[++n] = s[i];
    }
    a[++n] = '#';
    int p = 0, mx = 0;
    for (int i = 1; i < n; ++i) {
        r[i] = mx > i ? min(r[2 * p - i], mx - i) : 1;
        for (; a[i - r[i]] == a[i + r[i]]; ++r[i]);
        if (i + r[i] > mx) {
            p = i;
            mx = i + r[i];
        }
    }
    for (int i = 2, j = 3; i < n; ++i)
        for (; j <= i + r[i] - 1; ++j)
            if (a[j] == '#')
                c[j] = j - i;
    for (int i = n - 1, j = n - 2; i > 1; --i)
        for (; j >= i - r[i] + 1; --j)
            if (c[j])
                c[j] += i - j;
    int ans = 0;
    for (int i = 2; i < n; ++i)
        if (c[i] > ans)
            ans = c[i];
    printf("%d\n", ans);
    return 0;
}
