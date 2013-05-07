#include <cctype>
#include <cstdio>
#include <map>

using namespace std;

typedef map<int, int> MII;
typedef MII::iterator MIT;

const int MAXL = 111111, MAXN = 22222, MAXM = 55555, MAXB = 3333333;

char buf[MAXB], *h = buf;
int a[MAXL << 1], g[MAXL], v[MAXL], p[MAXL], q[MAXL], f[MAXL], s[MAXN], id[MAXM];
MII nxt[MAXL];

inline int getint() {
    for (; !isdigit(*h); ++h);
    int ret = *h++ - 48;
    for (; isdigit(*h); (ret *= 10) += *h++ - 48);
    return ret;
}

int main() {
    fread(buf, 1, MAXB - 10, stdin);
    int n = getint(), m = getint(), tot = 0, r = -1;
    for (int i = 1, j = -1; i <= n; ++i)
        for (int d = 0; d < 2; ++d)
            for (int k = a[++j] = getint(); k--; )
                a[++j] = getint();
    for (int i = 0; i < m; ++i) {
        int &x = id[i];
        for (int c, k = getint(); k--; x = nxt[x][c])
            if (!nxt[x][c = getint()])
                nxt[x][c] = ++tot;
        ++g[x];
    }
    for (MIT it = nxt[0].begin(); it != nxt[0].end(); ++it)
        q[++r] = it->second;
    for (int l = 0; l <= r; ++l)
        for (MIT it = nxt[q[l]].begin(); it != nxt[q[l]].end(); ++it) {
            q[++r] = it->second;
            int x = p[q[l]];
            for (; x && !nxt[x][it->first]; x = p[x]);
            p[q[r]] = nxt[x][it->first];
        }
    for (int i = 1, j = 0; i <= n; ++i)
        for (int d = 0; d < 2; ++d)
            for (int k = a[j++], x = 0; k--; ++j) {
                for (; x && !nxt[x][a[j]]; x = p[x]);
                for (int t = x = nxt[x][a[j]]; t && v[t] != i; t = p[t]) {
                    v[t] = i;
                    s[i] += g[t];
                    ++f[t];
                }
            }
    for (int i = 0; i < m; ++i)
        printf("%d\n", f[id[i]]);
    for (int i = 1; i < n; ++i)
        printf("%d ", s[i]);
    printf("%d\n", s[n]);
    return 0;
}
