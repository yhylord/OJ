#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long LL;

const int MAXL = 111, MAXN = 33;

char s[11];
bool v[MAXN][MAXL][1 << 10];
int nxt[MAXL][26], p[MAXL], q[MAXL], g[MAXL], h[MAXN][MAXL][1 << 10], e[1111][4];
LL f[MAXN][MAXL][1 << 10];
string tmp;
vector<string> w;

void work(int i, int j, int t, string cur) {
    if (i)
        for (int k = h[i][j][t]; k; k = e[k][3])
            work(i - 1, e[k][0], e[k][1], char(e[k][2]) + cur);
    else
        w.push_back(cur);
}

int main() {
    int n, m, tot = 0, cnt = 0, r = -1;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int x = 0;
        scanf("%s", s);
        for (int j = 0; s[j]; x = nxt[x][s[j++] - 'a'])
            if (!nxt[x][s[j] - 'a'])
                nxt[x][s[j] - 'a'] = ++tot;
        g[x] |= 1 << i;
    }
    for (int k = 0; k < 26; ++k)
        if (nxt[0][k])
            q[++r] = nxt[0][k];
    for (int l = 0; l <= r; ++l)
        for (int k = 0; k < 26; ++k) {
            int x = p[q[l]];
            for (; x && !nxt[x][k]; x = p[x]);
            if (nxt[q[l]][k]) {
                p[q[++r] = nxt[q[l]][k]] = nxt[x][k];
                g[q[r]] |= g[p[q[r]]];
            }
            else
                nxt[q[l]][k] = nxt[x][k];
        }
    f[0][0][0] = 1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= tot; ++j)
            for (int t = 0; t < 1 << m; ++t)
                if (f[i][j][t])
                    for (int k = 0; k < 26; ++k)
                        f[i + 1][nxt[j][k]][t | g[nxt[j][k]]] += f[i][j][t];
    LL ans = 0;
    for (int i = 0; i <= tot; ++i)
        if (f[n][i][(1 << m) - 1]) {
            v[n][i][(1 << m) - 1] = true;
            ans += f[n][i][(1 << m) - 1];
        }
    printf("%lld\n", ans);
    if (ans <= 42) {
        for (int i = n - 1; i >= 0; --i)
            for (int j = 0; j <= tot; ++j)
                for (int t = 0; t < 1 << m; ++t)
                    if (f[i][j][t])
                        for (int k = 0; k < 26; ++k)
                            if (v[i + 1][nxt[j][k]][t | g[nxt[j][k]]]) {
                                v[i][j][t] = true;
                                e[++cnt][0] = j;
                                e[cnt][1] = t;
                                e[cnt][2] = k + 'a';
                                e[cnt][3] = h[i + 1][nxt[j][k]][t | g[nxt[j][k]]];
                                h[i + 1][nxt[j][k]][t | g[nxt[j][k]]] = cnt;
                            }
        for (int i = 0; i <= tot; ++i)
            if (v[n][i][(1 << m) - 1])
                work(n, i, (1 << m) - 1, "");
        sort(w.begin(), w.end());
        for (vector<string>::iterator it = w.begin(); it != w.end(); ++it)
            cout << *it << endl;
    }
    return 0;
}
