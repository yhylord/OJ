SPOJ BOXES

【题目大意】

给出环形排列的N(1 <= N <= 1000)个盒子和每个盒子里的球数，每个盒子向相邻盒子里移动一个球的代价为1，求使得每个盒子里球数不超过1的最小代价。

【算法分析】

球的传递好比流的过程，因此我们将源点S向各盒子连容量为初始球数费用为0的边，每个盒子向相邻盒子连容量正无穷费用为1的边，同时每个盒子向汇点连容量为1费用为0的边，易得求出最小费用最大流即可得到满足限制的最小代价。时间复杂度O(UN^3)。
