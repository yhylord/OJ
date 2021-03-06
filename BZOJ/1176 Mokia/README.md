BZOJ 1176 Mokia

题目明显满足允许离线，修改独立的条件，故考虑对时间分治。

我们知道，Query(x1, y1, x2, y2) = Query(1, y1, x2, y2) - Query(1, y1, x1 - 1, y2)，从而把一个询问拆为两个形如Query(x, y1, y2)的部分和询问。

那么，我们把[l, mid]里的修改操作按x坐标排序，把[mid + 1, r]里拆解后的询问也按x坐标排序，然后按x坐标从小到大依次处理，每次查询Sum(y1, y2)就可以了。

因为我们只要修改点查询区间，用树状数组很容易维护，从而完成了[l, mid]对[mid + 1, r]的更新。

设总操作数为N，则时间复杂度O(NlogNlogW)。
