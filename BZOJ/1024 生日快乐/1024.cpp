#include <algorithm>
#include <cstdio>

using namespace std;

double dfs(double x, double y, int c) {
    if (c == 1)
        return max(x, y) / min(x, y);
    double ret = 11111;
    for (int i = 1; i < c; ++i) {
        ret = min(ret, max(dfs(x / c * i, y, i), dfs(x / c * (c - i), y, c - i)));
        ret = min(ret, max(dfs(x, y / c * i, i), dfs(x, y / c * (c - i), c - i)));
    }
    return ret;
}

int main() {
    double x, y;
    int n;
    scanf("%lf%lf%d", &x, &y, &n);
    printf("%.6lf\n", dfs(x, y, n));
    return 0;
}
