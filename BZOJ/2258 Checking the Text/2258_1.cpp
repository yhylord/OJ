#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long LL;

const int MAXN = 55555, BASE1 = 10007, BASE2 = 10009, MOD1 = 1000000007, MOD2 = 1000000009;

char s[MAXN];
int pos[MAXN], id[MAXN];
LL p1[MAXN], p2[MAXN], h1[MAXN], h2[MAXN];

inline int get1(int x, int l) {
    return ((h1[x + l - 1] - h1[x - 1] * p1[l]) % MOD1 + MOD1) % MOD1;
}

inline int get2(int x, int l) {
    return ((h2[x + l - 1] - h2[x - 1] * p2[l]) % MOD2 + MOD2) % MOD2;
}

int main() {
    p1[0] = p2[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        p1[i] = p1[i - 1] * BASE1 % MOD1;
        p2[i] = p2[i - 1] * BASE2 % MOD2;
    }
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    for (int i = 1; i <= len; ++i) {
        h1[i] = (h1[i - 1] * BASE1 + s[i] + 1) % MOD1;
        h2[i] = (h2[i - 1] * BASE2 + s[i] + 1) % MOD2;
        pos[id[i] = i] = i;
    }
    int n;
    scanf("%d", &n);
    while (n--) {
        char op;
        scanf(" %c", &op);
        if (op == 'I') {
            char c;
            int p;
            scanf(" %c%d", &c, &p);
            for (int i = ++len; i > p; --i) {
                s[i] = s[i - 1];
                pos[id[i] = id[i - 1]] = i;
            }
            s[p] = c;
            id[p] = 0;
            for (int i = p; i <= len; ++i) {
                h1[i] = (h1[i - 1] * BASE1 + s[i] + 1) % MOD1;
                h2[i] = (h2[i - 1] * BASE2 + s[i] + 1) % MOD2;
            }
        }
        else {
            int x, y;
            scanf("%d%d", &x, &y);
            x = pos[x], y = pos[y];
            int l = -1, r = len - max(x, y) + 2;
            while (l + 1 < r) {
                int mid = l + r >> 1;
                if (get1(x, mid) == get1(y, mid) && get2(x, mid) == get2(y, mid))
                    l = mid;
                else
                    r = mid;
            }
            printf("%d\n", l);
        }
    }
    return 0;
}
