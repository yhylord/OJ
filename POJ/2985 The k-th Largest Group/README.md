POJ 2985 The k-th Largest Group

【题目大意】

编号为1~N(1 <= N <= 200000)的猫各自成一组，有M(1 <= M <= 200000)次操作：把两只猫所在的组合并；输出当前的第k大组的大小。

【算法分析】

集合的合并很显然是用并查集来解决的，接下来就是对size的维护了，使用权值线段树或者平衡树（要合并同权值结点）皆可，时间复杂度O(MlogN)。
