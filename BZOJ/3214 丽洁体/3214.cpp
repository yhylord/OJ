#include <cstdio>

typedef long long LL;

const int MAXN = 55555, BASE = 128;

struct para {
    int len;
    LL w[MAXN];

    inline void get() {
        char c;
        LL t = 0;
        scanf(" ");
        while ((c = getchar()) != '\r') {
            if (c == ' ') {
                if (t)
                    w[++len] = t, t = 0;
                continue;
            }
            t = t * BASE + c;
        }
        if (t)
            w[++len] = t;
    }
} a, b, c, d;

int main() {
    int ans = 0, mn = 1000000000;
    d.get(), a.get(), b.get(), c.get();
    int bg = 1, ed = d.len;
    for (int i = 1; i <= a.len; ++i, ++bg)
        for (; d.w[bg] != a.w[i]; ++bg, ++ans);
    for (int i = c.len; i; --i, --ed)
        for (; d.w[ed] != c.w[i]; --ed, ++ans);
    for (; bg <= ed; ++bg)
        if (d.w[bg] == b.w[1]) {
            int i = 2, j = bg + 1, p = 0;
            for (; i <= b.len && j <= ed; ++i, ++j) {
                for (; d.w[j] != b.w[i] && j <= ed; ++j, ++p);
                if (j > ed)
                    break;
            }
            if (i > b.len && p < mn)
                mn = p;
        }
    printf("%d\n", ans + mn);
    return 0;
}
