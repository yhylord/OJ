BZOJ 2258 Checking the Text

这种求LCP的问题，通常可以想到用后缀数组或者二分 + 字符串Hash的方法来解决。

由于插入操作较少，可以选择暴力插入重建Hash或者后缀数组。

时间复杂度O(I|L| + Qlog|L|)。
