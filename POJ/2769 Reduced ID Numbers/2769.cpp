#include <cstdio>

const int MAXN = 333, MAXS = 1111111;

int a[MAXN], v[MAXS];

int main() {
    int t, idx = 0;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        for (int i = n; ; ++i) {
            bool f = true;
            ++idx;
            for (int j = 1; f && j <= n; ++j)
                if (v[a[j] % i] == idx)
                    f = false;
                else
                    v[a[j] % i] = idx;
            if (f) {
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}
