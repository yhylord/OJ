BZOJ 1657 Mooo

我们很容易发现，对于奶牛i, j(i < j)，假如h_i < h_j，那么奶牛i对于所有编号大于j的奶牛都是没有意义的，因此我们维护一个身高的单调栈（单调减）即可方便地完成更新答案的过程。时间复杂度O(N)。
