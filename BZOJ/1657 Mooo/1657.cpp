#include <climits>
#include <cstdio>

const int MAXN = 55555;

int top, s[MAXN], a[MAXN], b[MAXN], c[MAXN];

inline void work(int i) {
    for (; a[i] >= a[s[top]]; --top);
    c[s[top]] += b[i];
    s[++top] = i;
}

int main() {
    int n, ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &a[i], &b[i]);
    a[top = 0] = INT_MAX;
    for (int i = 1; i <= n; ++i)
        work(i);
    top = 0;
    for (int i = n; i; --i)
        work(i);
    for (int i = 1; i <= n; ++i)
        if (c[i] > ans)
            ans = c[i];
    printf("%d\n", ans);
    return 0;
}
