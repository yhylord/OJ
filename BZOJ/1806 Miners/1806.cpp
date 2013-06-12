#include <cstdio>
#include <cstring>

const int MAXN = 111111;

char s[MAXN];
int id[333], f[2][4][4][4][4];

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

int main() {
    int n, ans = 0;
    scanf("%d%s", &n, s);
    id['M'] = 1, id['F'] = 2, id['B'] = 3;
    memset(f[0], -1, sizeof f[0]);
    f[0][0][0][0][0] = 0;
    for (int i = 0; i < n; ++i) {
        int c = id[s[i]], p = i & 1, q = p ^ 1;
        memset(f[q], -1, sizeof f[q]);
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k)
                for (int l = 0; l < 4; ++l)
                    for (int m = 0; m < 4; ++m)
                        if (~f[p][j][k][l][m]) {
                            checkmax(f[q][k][c][l][m], f[p][j][k][l][m] + (j == 1 || k == 1 || c == 1) + (j == 2 || k == 2 || c == 2) + (j == 3 || k == 3 || c == 3));
                            checkmax(f[q][j][k][m][c], f[p][j][k][l][m] + (l == 1 || m == 1 || c == 1) + (l == 2 || m == 2 || c == 2) + (l == 3 || m == 3 || c == 3));
                        }
    }
    for (int j = 0; j < 4; ++j)
        for (int k = 0; k < 4; ++k)
            for (int l = 0; l < 4; ++l)
                for (int m = 0; m < 4; ++m)
                    checkmax(ans, f[n & 1][j][k][l][m]);
    printf("%d\n", ans);
    return 0;
}
