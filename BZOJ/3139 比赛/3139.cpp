#include <algorithm>
#include <cstdio>
#include <map>

using namespace std;

typedef long long LL;

const int MAXN = 11, MOD = 1000000007;

map<LL, bool> v;
map<LL, int> f;

struct data {
    int a[MAXN];

    inline LL hash() {
        LL ret = 0;
        for (int i = 1; i <= a[0]; ++i)
            (ret *= 29) += a[i] + 1;
        return ret;
    }
} bg;

int dfs(int dep, data d) {
    int n = d.a[0];
    if (dep == n) {
        if (d.a[n])
            return 0;
        if (n == 1)
            return 1;
        sort(d.a + 1, d.a + (n = --d.a[0]) + 1);
        LL t = d.hash();
        if (!v[t]) {
            f[t] = dfs(1, d);
            v[t] = true;
        }
        return f[t];
    }
    int ret = 0;
    if (d.a[n] >= 3 && 3 * (n - 2) >= d.a[dep]) {
        d.a[n] -= 3;
        (ret += dfs(dep + 1, d)) %= MOD;
        d.a[n] += 3;
    }
    if (d.a[n] >= 1 && d.a[dep] >= 1 && 3 * (n - 1 - dep) >= d.a[n] - 1 && 3 * (n - 2) >= d.a[dep] - 1) {
        --d.a[n];
        --d.a[dep];
        (ret += dfs(dep + 1, d)) %= MOD;
        ++d.a[n];
        ++d.a[dep];
    }
    if (d.a[dep] >= 3 && 3 * (n - 1 - dep) >= d.a[n]) {
        d.a[dep] -= 3;
        (ret += dfs(dep + 1, d)) %= MOD;
        d.a[dep] += 3;
    }
    return ret;
}

int main() {
    scanf("%d", &bg.a[0]);
    for (int i = 1; i <= bg.a[0]; ++i)
        scanf("%d", &bg.a[i]);
    printf("%d\n", dfs(1, bg));
    return 0;
}
