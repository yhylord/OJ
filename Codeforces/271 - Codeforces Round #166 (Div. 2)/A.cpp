#include <cstdio>

int main() {
    int y;
    scanf("%d", &y);
    for (++y; y < 10000; ++y) {
        int a = y / 1000, b = y / 100 % 10, c = y / 10 % 10, d = y % 10;
        if (a != b && a != c && a != d && b != c && b != d && c != d) {
            printf("%d\n", y);
            break;
        }
    }
    return 0;
}
