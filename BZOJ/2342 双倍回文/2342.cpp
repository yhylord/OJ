#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 1111111;

char s[MAXN], a[MAXN];
int f[MAXN], r[MAXN];

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

int main() {
    scanf("%*d%s", s);
    a[0] = '$';
    int n = 0, ans = 0;
    for (int i = 0; s[i]; ++i) {
        a[++n] = '#';
        a[++n] = s[i];
    }
    a[++n] = '#';
    int p = 0, mx = 0;
    for (int i = 1; i < n; ++i) {
        f[i] = i + (a[i] != '#');
        r[i] = mx > i ? min(r[2 * p - i], mx - i) : 1;
        for (; a[i - r[i]] == a[i + r[i]]; ++r[i]);
        if (i + r[i] > mx) {
            p = i;
            mx = i + r[i];
        }
    }
    f[n] = n;
    for (int i = 3; i < n; i += 2) {
        int l = max(i - r[i] / 2, 1), c = find(l);
        for (; c < i && c + r[c] - 1 < i; c = f[c] = find(c + 1));
        ans = max(ans, i - c << 1);
    }
    printf("%d\n", ans);
    return 0;
}
