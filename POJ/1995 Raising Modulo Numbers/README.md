POJ 1995 Raising Modulo Numbers

【题目大意】

给出M(1 <= M <= 45000)和H(1 <= H <= 45000)组Ai, Bi（不同时为0），求sigma{Ai^Bi} mod M。

【算法分析】

对于每组进行快速幂并求和即可，时间复杂度O(HlogB)。
