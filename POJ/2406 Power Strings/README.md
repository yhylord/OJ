POJ 2406 Power Strings

【题目大意】

一个字符串A(1 <= |A| <= 1000000)可以写成某一个子串B重复N次所得，记为A = B^N，求最大的N。

【算法分析】

令L = |A|，容易发现，用KMP自匹配后L - p[L]即得到最小覆盖子串的长度。

下面我们要证明一个问题：一个字符串的覆盖子串长度，一定是它的最小覆盖子串长度的倍数。

设最小覆盖子串长度d整除L, 假设存在u > d满足u整除L且d不整除u。

易得，A_i = A_(i + d)，A_i = A_(i + u)，则A_(i + d) = A_(i + u)，即A_i = A_(i + u - d)，不断进行可得到A_i = A(i + u - kd)（k为正整数）。

因为d不整除u，那么必然存在k使得0 < u - kd < d，与d是最小循环子串长度矛盾。

所以，最小覆盖子串长度若为L的约数则得解否则输出1。时间复杂度O(L)。
