POJ 2115 C Looooops

【题目大意】

问在K(1 <= K <= 32)位二进制整数类型下，循环for (var = A; var != B; var += C) statement;(0 <= A, B, C < 2^K)执行多少次结束。

【算法分析】

由题意我们可列出A + Cx = B(mod 2^K)，即Cx + 2^Ky = B - A。

这就转化为求ax + by = c这个二元一次不定方程的最小的x了，用扩展欧几里得算法即可。时间复杂度O(logN)。
