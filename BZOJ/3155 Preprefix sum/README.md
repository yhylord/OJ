BZOJ 3155 Preprefix sum

由题意，ss_i = sigma{a_k * (i - k + 1)}, 1 <= k <= i。

为了方便，我们维护两个树状数组，s1_i = sigma{a_k}, 1 <= k <= i，s2_i = sigma{a_k * (n - k + 1)}, 1 <= k <= i。

那么，显然ss_i = s2_i - s1_i * (n - i)。

时间复杂度O((N + M)logN)。
