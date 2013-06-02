#include <cstdio>

const int MAXN = 5555, MOD = 100000000;

char a[MAXN], b[MAXN];
int f[MAXN], g[MAXN];

inline void add(int &x, int y) {
    if ((x += y) >= MOD)
        x -= MOD;
}

int main() {
    scanf("%s%s", a, b);
    for (int i = 0; a[i] != '.'; ++i) {
        int mx = 0, s = 1;
        for (int j = 0; b[j] != '.'; ++j) {
            int tf = f[j], tg = g[j];
            if (a[i] == b[j])
                if (mx + 1 > f[j])
                    f[j] = mx + 1, g[j] = s;
                else if (mx + 1 == f[j])
                    add(g[j], s);
            if (tf > mx)
                mx = tf, s = tg;
            else if (tf == mx)
                add(s, tg);
        }
    }
    int mx = 0, s = 0;
    for (int i = 0; b[i] != '.'; ++i)
        if (f[i] > mx)
            mx = f[i], s = g[i];
        else if (f[i] == mx)
            add(s, g[i]);
    printf("%d\n%d\n", mx, s);
    return 0;
}
