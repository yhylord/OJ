BZOJ 3227 红黑树

用f[i][j][0/1]表示黑高度为i，结点个数为j，根为红/黑的最优解，通过枚举儿子结点个数转移是显然的，但是复杂度为O(N^3)。

我们发现，由于红黑树是平衡的，高度不会超过logN，因此第一位不会超过logN，这样时间复杂度就变为O(N^2logN)。
