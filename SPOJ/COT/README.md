SPOJ COT

【题目大意】

给出一棵N(1 <= N <= 100000)个点的树，有M(1 <= M <= 100000)次询问，每次询问u到v路径上的第k小边。

【算法分析】

考虑使用可持久化线段树解决。

我们用T_i表示加入根到i路径上的数形成的权值线段树，那么它可以通过T_father(i)插入a_i得到。易得，路径u -> v上的数形成的权值线段树T = T_u + T_v - T_LCA(u, v) - T_father(LCA(u, v))，再查询第k大即可。

其中LCA可以使用倍增算法实现，需要注意的是，上述插入a_i的顺序也要按照DFS序。整体时间复杂度为O(NlogN)。
