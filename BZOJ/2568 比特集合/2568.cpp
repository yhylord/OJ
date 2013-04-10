#include <algorithm>
#include <cstdio>
#include <set>

using namespace std;

char op[11];
int a[22][66666];
multiset<int> e;

inline int sum(int p, int x) {
    int ret = 0;
    for (; x; x -= x & -x)
        ret += a[p][x];
    return ret;
}

inline void add(int p, int x, int v) {
    for (; x <= 1 << 16; x += x & -x)
        a[p][x] += v;
}

int main() {
    int m, x, s = 0;
    scanf("%d", &m);
    while (m--) {
        scanf("%s%d", op, &x);
        if (op[0] == 'A')
            s += x;
        else if (op[0] == 'I') {
            e.insert(x - s);
            for (int i = 0; i < 16; ++i)
                add(i, ((x - s) & ((1 << i + 1) - 1)) + 1, 1);
        }
        else if (op[0] == 'D') {
            int t = e.count(x - s);
            for (int i = 0; i < 16; ++i)
                add(i, ((x - s) & ((1 << i + 1) - 1)) + 1, -t);
            while (t--)
                e.erase(x - s);
        }
        else {
            int l = 1 << x, r = (1 << x + 1) - 1, ans = 0;
            ans += sum(x, min(max(r - (s & ((1 << x + 1) - 1)) + 1, 0), 1 << 16));
            ans -= sum(x, min(max(l - (s & ((1 << x + 1) - 1)), 0), 1 << 16));
            l += 1 << x + 1, r += 1 << x + 1;
            ans += sum(x, min(max(r - (s & ((1 << x + 1) - 1)) + 1, 0), 1 << 16));
            ans -= sum(x, min(max(l - (s & ((1 << x + 1) - 1)), 0), 1 << 16));
            printf("%d\n", ans);
        }
    }
    return 0;
}
