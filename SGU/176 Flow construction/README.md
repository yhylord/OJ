SGU 176 Flow construction

【题目大意】

给出一个N个点(1 <= N <= 100)M条边的有向图，每条边有容量，有一些边必须流满，指定源汇，求由源点产生的最小流。

【算法分析】

有源汇的最小流问题，一般的方法是首先用上题的方法求出可行流，注意由于有源汇我们要添加原图中从汇到源容量正无穷的边后再做，然后删去新源新汇和正无穷辅助边后在从原图的汇到源做最大流，两者相减即为答案。

然而考虑这题的特殊性，指定的源汇都可以有出入边，从而导致非法的退流（退的流并不是源点产生的流），因此，为了方便处理，我们再新建超级源连容量正无穷边到原图中源，从原图中汇向新建超级汇连容量正无穷边，再进行上述操作，从而转化为一个已知的问题。时间复杂度O(MN^2)。
