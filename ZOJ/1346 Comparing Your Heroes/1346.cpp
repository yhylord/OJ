#include <cstring>
#include <iostream>
#include <string>
#include <map>

using namespace std;

const int MAXN = 17;

bool g[MAXN][MAXN];
int c[MAXN];
long long f[1 << MAXN - 1];
string a, b;
map<string, int> h;

int main() {
    int m;
    while (cin >> m) {
        int n = 0;
        h.clear();
        memset(g, false, sizeof g);
        while (m--) {
            cin >> a >> b;
            if (!h[a])
                h[a] = ++n;
            if (!h[b])
                h[b] = ++n;
            g[h[a]][h[b]] = true;
        }
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    g[i][j] |= g[i][k] & g[k][j];
        for (int i = 1; i <= n; ++i) {
            c[i - 1] = 0;
            for (int j = 1; j <= n; ++j)
                c[i - 1] |= g[i][j] << j - 1;
        }
        f[0] = 1;
        for (int i = 1; i < 1 << n; ++i) {
            f[i] = 0;
            for (int j = 0; j < n; ++j)
                if (((i >> j) & 1) && !(c[j] & i))
                    f[i] += f[i ^ (1 << j)];
        }
        cout << f[(1 << n) - 1] << endl;
    }
    return 0;
}
