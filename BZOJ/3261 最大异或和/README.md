BZOJ 3261 最大异或和

令s_N = a_1 xor a_2 xor ... xor a_N。

对于s建立可持久化Trie，添加操作不成问题。

询问即要求x xor s_N xor s_k(l - 1 <= k <= r - 1)最大，在可持久化Trie上贪心找即可。

时间复杂度O((N + M)logA)。
