BZOJ 1040 骑士

由于每个点都对应一条边，任意一个N个点的连通块都有N条边，故每个连通块都是环套树。

首先考虑树上的DP，用f[i][0/1]表示第i个点不取/取的最优解，很容易从儿子转移。

再考虑环上的DP，破环为链后，用g[i][0/1][0/1]表示链首不取/取，第i个点不取/取的最优解，很容易从i - 1转移。

最后只要把每个环上的合法最优解加起来就可以了。

至于找环，可以DFS，也可以通过不断删除度为1的点来完成。

时间复杂度O(N)。
