BZOJ 3164 Eden的博弈树

叶子结点的答案是已经确定的了，考虑树形DP。

我们要记录每个结点的最小黑集合大小，最小白集合大小，关键点集合大小，关键点集合最小元素，关键点集合异或和。

对于一个黑点，其最小黑集合大小为儿子最小黑集合大小的最小值，最小白集合大小为所有儿子最小白集合大小的和。

而关键点集合的维护，实际上只要把最小黑集合大小与当前结点最小黑集合大小相等的儿子的关键点集合并起来就可以了（因为这个儿子的最小白集合必然在当前结点的最小白集合中）。

对于白点同理。时间复杂度O(N)。
