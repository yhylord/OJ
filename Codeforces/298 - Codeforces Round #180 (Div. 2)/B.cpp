#include <cstdio>

int need[333];

int main() {
    int t, sx, sy, ex, ey;
    scanf("%d%d%d%d%d ", &t, &sx, &sy, &ex, &ey);
    int nx = ex - sx, ny = ey - sy;
    if (nx > 0)
        need['E'] = nx;
    else if (nx < 0)
        need['W'] = -nx;
    if (ny > 0)
        need['N'] = ny;
    else if (ny < 0)
        need['S'] = -ny;
    for (int i = 1; i <= t; ++i) {
        char c = getchar();
        if (need[c] > 0)
            --need[c];
        if (need['E'] + need['W'] + need['N'] + need['S'] == 0) {
            printf("%d\n", i);
            return 0;
        }
    }
    puts("-1");
    return 0;
}
