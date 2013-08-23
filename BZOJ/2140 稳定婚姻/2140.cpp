#include <cstdio>
#include <iostream>
#include <map>
#include <string>

using namespace std;

const int MAXN = 4444, MAXM = 22222;

bool v[MAXN];
int idx, cnt, dfn[MAXN], low[MAXN], c[MAXN], s[MAXN], sz[MAXN], h[MAXN], p[MAXM], nxt[MAXM];
map<string, int> g, b;
string name;

inline void checkmin(int &x, int y) {
    if (y < x)
        x = y;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++idx;
    v[s[++s[0]] = x] = true;
    for (int k = h[x]; k; k = nxt[k])
        if (!dfn[p[k]]) {
            tarjan(p[k]);
            checkmin(low[x], low[p[k]]);
        }
        else if (v[p[k]])
            checkmin(low[x], dfn[p[k]]);
    if (dfn[x] == low[x]) {
        ++cnt;
        do {
            ++sz[c[s[s[0]]] = cnt];
            v[s[s[0]]] = false;
        } while (s[s[0]--] != x);
    }
}

int main() {
    int n, m;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> name;
        g[name] = i;
        cin >> name;
        b[name] = i;
    }
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> name;
        int x = g[name];
        cin >> name;
        p[i] = b[name];
        nxt[i] = h[x];
        h[x] = i;
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; ++i)
        cout << (sz[c[i]] == 1 ? "Safe\n" : "Unsafe\n");
    return 0;
}
