#include <algorithm>
#include <climits>
#include <cstdio>
#include <queue>

using namespace std;

const int MAXN = 1111111, MAXK = 66;

int a[MAXN], s[MAXK], c[MAXK], u[MAXK];
priority_queue<pair<int, int> > q;

inline void checkmax(int &x, int y) {
    if (y > x)
        x = y;
}

inline void checkmin(int &x, int y) {
    if (y < x)
        x = y;
}

int main() {
    int n, k, r = 0, ans = INT_MAX;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; ++i) {
        scanf("%d", &c[i]);
        s[i] = s[i - 1] + c[i];
        for (int j = s[i - 1] + 1; j <= s[i]; ++j)
            scanf("%d", &a[j]);
        checkmax(r, a[s[i - 1] + (u[i] = 1)]);
        q.push(make_pair(-a[s[i - 1] + 1], i));
    }
    while (true) {
        checkmin(ans, r + q.top().first);
        int i = q.top().second;
        q.pop();
        if (++u[i] > c[i])
            break;
        checkmax(r, a[s[i - 1] + u[i]]);
        q.push(make_pair(-a[s[i - 1] + u[i]], i));
    }
    printf("%d\n", ans);
    return 0;
}
