#include <cstdio>

const double EPS = 1e-7;
const int MAXN = 111111, MAXD = 18;

double f[MAXN], a[MAXN], b[MAXN], c[MAXN], d[MAXN], ca[MAXN], cb[MAXN];
int p[MAXD][MAXN], s[MAXD][MAXN];

inline void checkmax(double &x, double y) {
    if (y > x)
        x = y;
}

inline double calc(int i, int j) {
    return a[i] * ca[j] + b[i] * cb[j];
}

void merge(int dep, int l, int r) {
    if (l == r) {
        p[dep][l] = l;
        return;
    }
    int mid = l + r >> 1;
    merge(dep + 1, l, mid);
    merge(dep + 1, mid + 1, r);
    for (int i = l, j = mid + 1, k = l; i <= mid || j <= r; ++k)
        p[dep][k] = j > r || i <= mid && d[p[dep + 1][i]] > d[p[dep + 1][j]] ? p[dep + 1][i++] : p[dep + 1][j++];
}

void solve(int dep, int l, int r) {
    if (l == r) {
        checkmax(f[l], f[l - 1]);
        cb[l] = f[l] / (b[l] + a[l] * c[l]);
        ca[l] = cb[l] * c[l];
        s[dep][l] = l;
        return;
    }
    int mid = l + r >> 1;
    solve(dep + 1, l, mid);
    for (int i = mid + 1, j = l; i <= r; ++i) {
        for (; j < mid && s[dep + 1][j + 1] && calc(p[dep + 1][i], s[dep + 1][j + 1]) > calc(p[dep + 1][i], s[dep + 1][j]); ++j);
        checkmax(f[p[dep + 1][i]], calc(p[dep + 1][i], s[dep + 1][j]));
    }
    solve(dep + 1, mid + 1, r);
    for (int i = l, j = mid + 1, k = l - 1; i <= mid && s[dep + 1][i] || j <= r && s[dep + 1][j]; ) {
        int x = j > r || !s[dep + 1][j] || i <= mid && s[dep + 1][i] && ca[s[dep + 1][i]] < ca[s[dep + 1][j]] ? s[dep + 1][i++] : s[dep + 1][j++];
        while (k > l && (ca[s[dep][k]] - ca[s[dep][k - 1]]) * (cb[x] - cb[s[dep][k]]) >= (cb[s[dep][k]] - cb[s[dep][k - 1]]) * (ca[x] - ca[s[dep][k]]))
            s[dep][k--] = 0;
        s[dep][++k] = x;
    }
}

int main() {
    int n;
    scanf("%d%lf", &n, &f[0]);
    for (int i = 1; i <= n; ++i) {
        scanf("%lf%lf%lf", &a[i], &b[i], &c[i]);
        d[i] = -a[i] / b[i];
    }
    merge(0, 1, n);
    solve(0, 1, n);
    printf("%.3lf\n", f[n]);
    return 0;
}
