#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 2222222;

char s[MAXN], a[MAXN];
int r[MAXN];

int main() {
    for (int cs = 1; gets(s) && s[0] != 'E'; ++cs) {
        a[0] = '$';
        int n = 0;
        for (int i = 0; s[i]; ++i) {
            a[++n] = '#';
            a[++n] = s[i];
        }
        a[++n] = '#';
        a[n + 1] = 0;
        int p = 0, mx = 0;
        for (int i = 1; i < n; ++i) {
            r[i] = mx > i ? min(r[2 * p - i], mx - i) : 1;
            for (; a[i + r[i]] == a[i - r[i]]; ++r[i]);
            if (i + r[i] > mx) {
                p = i;
                mx = i + r[i];
            }
        }
        int ans = 0;
        for (int i = 2; i < n; ++i)
            if (r[i] - 1 > ans)
                ans = r[i] - 1;
        printf("Case %d: %d\n", cs, ans);
    }
    return 0;
}
