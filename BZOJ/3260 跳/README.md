BZOJ 3260 跳

令题目中的C为D，C为组合，则D(x, y) = C(x + y, x)。

设N > M，易贪心地发现答案为N + 1 + D(N, 1) + D(N, 2) + ... + D(N, M) = N + 1 + C(N + 1, 1) + C(N + 2, 2) + ... + C(N + M, M) = N + 1 + (N + 1) / 1! + (N + 1) * (N + 2) / 2! + ... + (N + 1) * (N + 2) * ... * (N + M) / M!。

显然配合逆元就可以在O(MlogM)的时间复杂度内完成计算了。
