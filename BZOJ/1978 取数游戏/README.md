BZOJ 1978 取数游戏

实时维护f[i]表示以含约数i的数为结尾的最多取数个数。对于当前数x的答案为max{f[k]} + 1(k | x且k >= L)，再拿它去更新所有f[k](k | x)。时间复杂度O(Nsqrt(A))。
