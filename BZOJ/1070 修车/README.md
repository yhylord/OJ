BZOJ 1070 修车

一位车主对总等待时间的贡献值取决于修车人员和它是该位修车人员倒数第几个修的，于是我们想到把一个技术人员拆成N个点，表示这个技术人员第几个修这辆车产生的贡献值。

那么，我们只需要将源点向车主连容量1费用0的边，将各个拆出的维修人员点向汇点连容量1费用0的边，将车主向每个维修人员的每个维修位次连容量1费用相应贡献值的边，那么求出最小费用最大流一定对应着最优且合法的分配方案。时间复杂度O(N^4 * M^2)。
