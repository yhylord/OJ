#include <cctype>
#include <cstdio>
#include <cstring>

const int MAXN = 22222, MAXM = 555555, MAXS = 626, MAXB = 22222222;

char buf1[MAXB], *it1 = buf1, buf2[MAXB], *it2 = buf2;
int d[MAXN], q[MAXN], a[MAXS][33];
unsigned f[MAXN][MAXS];

struct adj {
    adj *nxt;
    int p;
} e[MAXM << 1], *h[MAXN], *tot = e;

inline int getint() {
    for (; !isdigit(*it1); ++it1);
    int ret = *it1++ - 48;
    for (; isdigit(*it1); (ret *= 10) += *it1++ - 48);
    return ret;
}

void putint(int x) {
    if (x / 10)
        putint(x / 10);
    *it2++ = x % 10 + 48;
}

inline void work() {
    memset(h, 0, sizeof h);
    int n = getint(), m = getint(), s = (n - 1 >> 5) + 1, r = -1;
    for (int i = 1; i <= n; ++i)
        a[i - 1 >> 5][i - 1 & 31] = getint();
    for (int i = 1; i <= m; ++i) {
        int x = getint();
        ++d[tot->p = getint()];
        tot->nxt = h[x];
        h[x] = tot++;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < s; ++j)
            f[i][j] = 0;
        f[i][i - 1 >> 5] = 1 << (i - 1 & 31);
        if (!d[i])
            q[++r] = i;
    }
    for (int l = 0; l <= r; ++l)
        for (adj *k = h[q[l]]; k; k = k->nxt)
            if (!--d[k->p])
                q[++r] = k->p;
    for (; r >= 0; --r) {
        int x = q[r];
        for (adj *k = h[x]; k; k = k->nxt) {
            int y = k->p;
            if ((f[x][y - 1 >> 5] & (1 << (y - 1 & 31))) == 0)
                for (int i = 0; i < s; ++i)
                    f[x][i] |= f[y][i];
        }
    }
    for (int i = 1; i <= n; ++i) {
        int ans = 0;
        for (int j = 0; j < s; ++j) {
            if (f[i][j] & 1)
                ans += a[j][0];
            if (f[i][j] & 2)
                ans += a[j][1];
            if (f[i][j] & 4)
                ans += a[j][2];
            if (f[i][j] & 8)
                ans += a[j][3];
            if (f[i][j] & 16)
                ans += a[j][4];
            if (f[i][j] & 32)
                ans += a[j][5];
            if (f[i][j] & 64)
                ans += a[j][6];
            if (f[i][j] & 128)
                ans += a[j][7];
            if (f[i][j] & 256)
                ans += a[j][8];
            if (f[i][j] & 512)
                ans += a[j][9];
            if (f[i][j] & 1024)
                ans += a[j][10];
            if (f[i][j] & 2048)
                ans += a[j][11];
            if (f[i][j] & 4096)
                ans += a[j][12];
            if (f[i][j] & 8192)
                ans += a[j][13];
            if (f[i][j] & 16384)
                ans += a[j][14];
            if (f[i][j] & 32768)
                ans += a[j][15];
            if (f[i][j] & 65536)
                ans += a[j][16];
            if (f[i][j] & 131072)
                ans += a[j][17];
            if (f[i][j] & 262144)
                ans += a[j][18];
            if (f[i][j] & 524288)
                ans += a[j][19];
            if (f[i][j] & 1048576)
                ans += a[j][20];
            if (f[i][j] & 2097152)
                ans += a[j][21];
            if (f[i][j] & 4194304)
                ans += a[j][22];
            if (f[i][j] & 8388608)
                ans += a[j][23];
            if (f[i][j] & 16777216)
                ans += a[j][24];
            if (f[i][j] & 33554432)
                ans += a[j][25];
            if (f[i][j] & 67108864)
                ans += a[j][26];
            if (f[i][j] & 134217728)
                ans += a[j][27];
            if (f[i][j] & 268435456)
                ans += a[j][28];
            if (f[i][j] & 536870912)
                ans += a[j][29];
            if (f[i][j] & 1073741824)
                ans += a[j][30];
            if (f[i][j] & 2147483648U)
                ans += a[j][31];
        }
        putint(ans);
        *it2++ = i == n ? '\n' : ' ';
    }
}

int main() {
    fread(buf1, 1, MAXB - 10, stdin);
    int t = getint();
    while (t--)
        work();
    fwrite(buf2, it2 - buf2, 1, stdout);
    return 0;
}
