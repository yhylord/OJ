POJ 2417 Discrete Logging

【题目大意】

给出质数P(2 <= P < 2^31), B(2 <= B < P)和N(1 <= N < P)，求最小的L使得B^L = N(mod P)或判断无解。

【算法分析】

由于P是质数，直接使用普通Baby-step Giant-step算法即可，时间复杂度O(sqrt(P))。
