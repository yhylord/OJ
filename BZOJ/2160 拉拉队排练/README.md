BZOJ 2160 拉拉队排练

首先我们用Manacher算法预处理出以i为起点的最长回文半径。我们发现，长度不超过N种。因此，我们可以很容易地利用区间统计出每种长度的个数。

接下来从高到低取前k个，每次使用快速幂即可。时间复杂度O(NlogN)。
