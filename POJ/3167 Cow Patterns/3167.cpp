#include <cstdio>
#include <cstring>

const int MAXN = 111111, MAXS = 33;

struct bit {
    int s[MAXS];

    inline void clear() {
        memset(s, 0, sizeof s);
    }

    inline void add(int x, int v) {
        for (; x < MAXS; x += x & -x)
            s[x] += v;
    }

    inline int sum(int x) {
        if (x < 0)
            return -1;
        int ret = 0;
        for (; x; x -= x & -x)
            ret += s[x];
        return ret;
    }
} s1, s2;

int a[MAXN], b[MAXN], p[MAXN], ans[MAXN];

int main() {
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; ++i)
        scanf("%d", &b[i]);
    for (int i = 2, j = 0; i <= m; ++i) {
        s2.add(b[i], 1);
        while (j && (s2.sum(b[i]) != s1.sum(b[j + 1]) + 1 || s2.sum(b[i] - 1) != s1.sum(b[j + 1] - 1))) {
            for (int k = j; k > p[j]; --k) {
                s1.add(b[k], -1);
                s2.add(b[i - k], -1);
            }
            j = p[j];
        }
        if (s2.sum(b[i]) == s1.sum(b[j + 1]) + 1 && s2.sum(b[i] - 1) == s1.sum(b[j + 1] - 1))
            s1.add(b[p[i] = ++j], 1);
    }
    s1.clear();
    s2.clear();
    for (int i = 1, j = 0; i <= n; ++i) {
        s2.add(a[i], 1);
        while (j && (s2.sum(a[i]) != s1.sum(b[j + 1]) + 1 || s2.sum(a[i] - 1) != s1.sum(b[j + 1] - 1))) {
            for (int k = j; k > p[j]; --k) {
                s1.add(b[k], -1);
                s2.add(a[i - k], -1);
            }
            j = p[j];
        }
        if (s2.sum(a[i]) == s1.sum(b[j + 1]) + 1 && s2.sum(a[i] - 1) == s1.sum(b[j + 1] - 1))
            s1.add(b[++j], 1);
        if (j == m)
            ans[++ans[0]] = i - m + 1;
    }
    printf("%d\n", ans[0]);
    for (int i = 1; i <= ans[0]; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
