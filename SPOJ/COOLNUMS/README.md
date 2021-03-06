SPOJ COOLNUMS

【题目大意】

定义各位数字可以分成两个和相等的集合的一类数叫cool number，比如23450：3+4+0 = 2+5。

求[A, B](1 <= A <= B <= 4 * 10^9)里有多少个cool number。

【算法分析】

首先，题目转化为[1, N]里有多少个cool number。

直接做的话可能有些困难，如果枚举了数位和再做，重复就很难处理了。

对于这样一种没法直接做但是性质和数位顺序无关的题目，我们可以用暴力一点的方法。

由于N <= 4 * 10^9，也就是数最多10位，我们可以枚举这个10位数里有几个0，几个1，几个2……

设枚举出来的数量为S，大约100000个，每个组合可以用一个11进制数来表示的。（不用把0的个数放在这个组合里面，因为0不影响判定结果，且数位DP本身就限定了长度）

然后我们可以用背包进行验证出可行方案作为数位DP的边界条件。

同时我们发现，任何一个N以内的数都是可以用这100000个组合里的一种表示出来的。

那么，用f[less][dep][state]表示是否已经小于N，到dep位，状态为state的数的个数，记忆化搜索就可以了。

设长度为L，转移复杂度为P（大约100），时间复杂度O(LPS)。
