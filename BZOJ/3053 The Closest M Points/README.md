BZOJ 3053 The Closest M Points

直接使用K-D Tree完成查询即可，由于是多维无需加优化，时间复杂度O(NlogN + TMN^((K - 1) / K))。
