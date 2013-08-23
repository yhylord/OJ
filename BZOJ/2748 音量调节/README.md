BZOJ 2748 音量调节

f(i, j)表示到第i首歌能否有音量j，转移到f(i + 1, k), k = j +/- c_(i + 1), k >= 0 && k <= maxLevel。

初始有f(0, beginLevel) = true。答案为f(N, k) = true的最大的k。

时间复杂度O(NmaxLevel)。
