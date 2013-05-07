#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

typedef vector<pair<int, int> > VPII;

const int MAXN = 111111;

struct edge {
    int p, nxt;
} e[MAXN];

char str[MAXN];
int tot, idx, dfn[MAXN], mx[MAXN], s[MAXN], h[MAXN], id[MAXN],
    pre[MAXN], nxt[MAXN][26], p[MAXN], q[MAXN], ans[MAXN];
VPII v[MAXN];

inline void add(int x, int v) {
    for (; x <= idx; x += x & -x)
        s[x] += v;
}

inline int sum(int x) {
    int ret = 0;
    for (; x; x -= x & -x)
        ret += s[x];
    return ret;
}

inline void addedge(int x, int y) {
    e[++tot].p = y;
    e[tot].nxt = h[x];
    h[x] = tot;
}

void dfs(int x) {
    mx[x] = dfn[x] = ++idx;
    for (int k = h[x]; k; k = e[k].nxt) {
        dfs(e[k].p);
        mx[x] = mx[e[k].p];
    }
}

int main() {
    int x = 0, tot = 0, n = 0, r = -1, m;
    gets(str);
    for (int i = 0; str[i]; ++i)
        if (str[i] == 'B')
            x = pre[x];
        else if (str[i] == 'P')
            id[++n] = x;
        else {
            if (!nxt[x][str[i] - 'a'])
                pre[nxt[x][str[i] - 'a'] = ++tot] = x;
            x = nxt[x][str[i] - 'a'];
        }
    for (int k = 0; k < 26; ++k)
        if (nxt[0][k])
            addedge(0, q[++r] = nxt[0][k]);
    for (int l = 0; l <= r; ++l)
        for (int k = 0; k < 26; ++k)
            if (nxt[q[l]][k]) {
                int x = p[q[l]];
                for (; x && !nxt[x][k]; x = p[x]);
                p[q[++r] = nxt[q[l]][k]] = nxt[x][k];
                addedge(p[q[r]], q[r]);
            }
    dfs(0);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        v[y].push_back(make_pair(id[x], i));
    }
    add(dfn[n = x = 0], 1);
    for (int i = 0; str[i]; ++i)
        if (str[i] == 'B') {
            add(dfn[x], -1);
            x = pre[x];
        }
        else if (str[i] == 'P')
            for (VPII::iterator it = v[++n].begin(); it != v[n].end(); ++it)
                ans[it->second] += sum(mx[it->first]) - sum(dfn[it->first] - 1);
        else
            add(dfn[x = nxt[x][str[i] - 'a']], 1);
    for (int i = 0; i < m; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
