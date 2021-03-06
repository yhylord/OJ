POJ 1741 Tree

【题目大意】

给出N(1 <= N <= 10000)个结点的树，求使得路径u -> v长度不超过k的点对(u, v)的个数。

【算法分析】

首先我们对这棵树进行点分治，接下来考虑处理以root为根的子树。

记d[x]为x到root的距离，那么我们把子树的所有结点的d拉出来，即转化为了a[x] + a[y] <= k的(x, y)对数，这是可以通过排序后扫一遍解决的。

然后，这样可能出现重复的情况（x, y在root的同一儿子内部），那么我们只需要再对root的每个儿子进行同样的操作，但是是从之前的答案中减去。

时间复杂度O(Nlog^2N)。
