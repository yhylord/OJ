BZOJ 1911 特别行动队

令s_i = x_1 + x_2 + ... + x_i，用f(i)表示编队到第i个士兵为止的最大总战斗力。

f(i) = max{f(j) + a(s_i - s_j)^2 + b(s_i - s_j) + c}(0 <= j < i)。

变形得f(i) = max{f(j) + a(s_j)^2 - bs_j - 2as_is_j} + a(s_i)^2 + bs_i + c。

令x = s_j, y = f(j) + a(s_j)^2 - bs_j - 2as_is_j，我们要max z = -2as_i * x + y，也即要使直线y = 2as_i * x + z的纵截距最大。

由于x单调增，斜率2as_i单调减，我们可以用单调队列维护上凸壳来完成斜率优化。时间复杂度O(N)。
