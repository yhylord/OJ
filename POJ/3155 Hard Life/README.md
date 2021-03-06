POJ 3155 Hard Life

【题目大意】

给出一个N个点(1 <= N <= 100)M条边(0 <= M <= 1000)的无向图，求它的一个子图，使得边数/点数最大。

【算法分析】

这是一个求最大密度子图的问题，考虑分数规划。二分答案k后，我们要求g(k) = max{|E| - k|V|}。

由于取出子图是一个依赖性问题（取了边就一定要取对应的点），我们将它转化为最大权闭合图来求解，原图中的边和点都作为新图中的点，表示边的点权值为1，表示点的点权值为-k。

以往的g(k)函数都只有一个零点，但由于最大权闭合图允许不取点，导致g(k)在一个零点之后恒为0，因此，我们要二分出的是那个临界位置的零点。

题中有M = 0的情况要特判，否则最大密度必然是会取到点的，可以用上面的方法得到正解。时间复杂度O(MN^2logN)。
