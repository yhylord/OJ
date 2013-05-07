POJ 3243 Clever Y

【题目大意】

给出X, Z, K(0 <= X, Z, K <= 10^9)，求满足X^Y = K(mod Z)的最小的Y或判断无解。

【算法分析】

直接使用扩展Baby-step Giant-step算法即可，时间复杂度O(sqrt(Z))。
