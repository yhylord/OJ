#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

const char a[][5] = {"aaab", "aaba", "abaa", "baaa", "aabb", "abba", "abab"};

double c[7][8], x[7], y[7];
int h[4][4];

int main() {
    int tot = 0, ans = 1000000;
    for (int i = 0; i < 4; ++i)
        for (int j = i + 1; j < 4; ++j)
            scanf("%lf", &c[h[i][j] = tot++][7]);
    x[6] = c[0][7];
    for (int k = 0; k < 7; ++k)
        for (int i = 0; i < 4; ++i)
            for (int j = i + 1; j < 4; ++j)
                if (a[k][i] != a[k][j])
                    c[h[i][j]][k] = 1;
    for (int k = 0; k < 6; ++k) {
        int t = -1;
        for (int i = k; i < 6 && !~t; ++i)
            if (c[i][k])
                t = i;
        for (int j = k; j <= 7; ++j)
            swap(c[k][j], c[t][j]);
        for (int i = k + 1; i < 6; ++i)
            if (c[i][k]) {
                double r = c[i][k] / c[k][k];
                for (int j = k; j <= 7; ++j)
                    c[i][j] -= c[k][j] * r;
            }
    }
    for (; x[6] >= 0; --x[6]) {
        double t = x[6];
        for (int i = 5; i >= 0; --i) {
            x[i] = c[i][7];
            for (int j = 6; j > i; --j)
                x[i] -= c[i][j] * x[j];
            if ((x[i] /= c[i][i]) < 0 || fabs(int(x[i]) - x[i]) > 1e-10)
                t = 1000000;
            else
                t += x[i];
        }
        if (t < ans) {
            ans = int(t);
            memcpy(y, x, sizeof x);
        }
    }
    if (ans == 1000000)
        puts("-1");
    else {
        printf("%d\n", ans);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 7; ++j)
                for (int k = 0; k < y[j]; ++k)
                    putchar(a[j][i]);
            putchar('\n');
        }
    }
    return 0;
}
