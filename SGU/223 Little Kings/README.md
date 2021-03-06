SGU 223 Little Kings

【题目大意】

在N * N(1 <= N <= 10)的棋盘上放K(1 <= K <= N^2)个国王（可攻击相邻的8个格子），求使它们无法互相攻击的方案数。

【算法分析】

首先我们用DFS求出一行的可能状态（即无相邻）共S种（经计算N = 10时S = 144），并记录下对应的1的个数。

那么，我们用f[i][j][k]表示到第i行为止，第i行状态为第j种，共放了k个国王的方案数，显然枚举上一行的状态就可以完成递推了。

判断合法的条件很简单，只要上一行的状态及其左移一位、右移一位与当前行and的结果都为0即可。

时间复杂度O(KNS^2)。
