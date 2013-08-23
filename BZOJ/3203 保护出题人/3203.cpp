#include <algorithm>
#include <cstdio>

using namespace std;

typedef long double LD;
typedef long long LL;

const int MAXN = 111111;

int q[MAXN];
LL d, a[MAXN], x[MAXN], s[MAXN];

inline LD slope(int i, int j) {
    return LD(s[i - 1] - s[j - 1]) / (i - j) / d;
}

inline LD calc(int i, int j) {
    return LD(s[i] - s[j - 1]) / (x[i] + (i - j) * d);
}

int main() {
    int n, top = 0;
    LD ans = 0;
    scanf("%d%lld", &n, &d);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld%lld", &a[i], &x[i]);
        s[i] = s[i - 1] + a[i];
        for (; top && slope(q[top], q[top - 1]) >= slope(i, q[top]); --top);
        q[++top] = i;
        int l = 0, r = top;
        while (l + 1 < r) {
            int t = (r - l + 1) / 3, m1 = l - 1 + t, m2 = l - 1 + t + t;
            if (calc(i, q[m1]) > calc(i, q[m2]))
                r = m2 - 1;
            else
                l = m1 + 1;
        }
        ans += max(calc(i, q[l]), calc(i, q[r]));
    }
    printf("%.0lf\n", double(ans));
    return 0;
}
