BZOJ 2561 最小生成树

以(u, v)出现在最小生成树上为例，考虑Kruskal算法的流程。若在处理权值比w(u, v)小的边时，已经能使u, v连通，那么(u, v)就不可能出现在最小生成树上。

因此，很自然的想法是这些小边里去掉最少的边使得u, v不连通，这就转化为了一个最小割问题。最大生成树同理。时间复杂度O(MN^2)。
