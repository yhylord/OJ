#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 55555, BASE = 41;

char s[MAXN];
int pos[MAXN], id[MAXN];
unsigned p[MAXN], h[MAXN];

inline unsigned get(int x, int l) {
    return h[x + l - 1] - h[x - 1] * p[l];
}

int main() {
    p[0] = 1;
    for (int i = 1; i < MAXN; ++i)
        p[i] = p[i - 1] * BASE;
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    for (int i = 1; i <= len; ++i) {
        h[i] = h[i - 1] * BASE + s[i] - 'a' + 1;
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
            for (int i = p; i <= len; ++i)
                h[i] = h[i - 1] * BASE + s[i] - 'a' + 1;
        }
        else {
            int x, y;
            scanf("%d%d", &x, &y);
            x = pos[x], y = pos[y];
            int l = -1, r = len - max(x, y) + 2;
            while (l + 1 < r) {
                int mid = l + r >> 1;
                if (get(x, mid) == get(y, mid))
                    l = mid;
                else
                    r = mid;
            }
            printf("%d\n", l);
        }
    }
    return 0;
}
