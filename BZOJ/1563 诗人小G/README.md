BZOJ 1563 诗人小G

令c_i表示第i个诗句的长度，f(x)表示到第x个为止的最小总代价，则f(x) = min{f(i) + w(i + 1, x)}(0 <= i < x)，其中w(i, j) = |j - i + sigma{c_k}(i <= k <= j) - L|^P。

对w满足四边形不等式的证明参见http://www.byvoid.com/blog/noi-2009-poet，故可以进行决策单调性优化，时间复杂度O(NlogN)。

需要注意的是，题目要求答案在10^18以内才输出，但在运算过程中是可能超出long long范围的，因此我们必须使用long double进行中间过程的运算，而不能直接把10^18作为运算过程的上界。
