BZOJ 2875 随机数生成器

题目给出的递推式很容易使用矩阵乘法 + 快速幂进行优化，由于模的范围是10^18需要使用快速乘防止溢出。

所谓快速乘，就是把其中一个乘数二进制拆分，用倍增的方法来求，这样就只需要用到加法和乘2了，时间复杂度O(logM)。

时间复杂度O(logNlogM)。
