#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

const int MAXN = 11, MAXS = 111111;

bool g[MAXN << 2];
int a[MAXN], c[MAXS];
map<unsigned, int> h;
unsigned f[MAXN][MAXS], v[MAXN][MAXS];

void dfs(int dep, int rem, int sum, unsigned state) {
    if (dep > 9) {
        if (rem)
            return;
        h[c[++c[0]] = state] = c[0];
        if (sum & 1)
            return;
        int goal = sum >> 1;
        memset(g, false, sizeof g);
        g[0] = true;
        for (int i = 1; i < 10; ++i)
            for (int j = 1; j <= a[i]; ++j)
                for (int k = goal; k >= i; --k)
                    g[k] |= g[k - i];
        if (g[goal] && state)
            f[0][c[0]] = 1;
        return;
    }
    for (int i = 0; i <= rem; ++i) {
        a[dep] = i;
        dfs(dep + 1, rem - i, sum + i * dep, dep ? state * 11 + a[dep] : 0);
    }
}

unsigned calc(bool less, int dep, int state) {
    if (!dep || less && v[dep][state])
        return f[dep][state];
    int b[MAXN], ed = less ? 9 : a[dep];
    unsigned ret = 0;
    v[dep][state] |= less;
    for (int i = 9, t = c[state]; i; --i, t /= 11)
        b[i] = t % 11;
    for (int i = 0; i <= ed; ++i) {
        ++b[i];
        unsigned ts = 0;
        for (int j = 1; j < 10; ++j)
            (ts *= 11) += b[j];
        ret += calc(less || i < a[dep], dep - 1, h[ts]);
        --b[i];
    }
    return less ? f[dep][state] = ret : ret;
}

inline unsigned get(unsigned x) {
    if (!x)
        return 0;
    a[0] = 0;
    for (; x; x /= 10)
        a[++a[0]] = x % 10;
    return calc(0, a[0], c[0]);
}

int main() {
    dfs(0, 10, 0, 0);
    unsigned x, y;
    while (scanf("%u%u", &x, &y) && x && y)
        printf("%u\n", get(y) - get(x - 1));
    return 0;
}
