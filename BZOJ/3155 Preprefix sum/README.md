BZOJ 3155 Preprefix sum

�����⣬ss_i = sigma{a_k * (i - k + 1)}, 1 <= k <= i��

Ϊ�˷��㣬����ά��������״���飬s1_i = sigma{a_k}, 1 <= k <= i��s2_i = sigma{a_k * (n - k + 1)}, 1 <= k <= i��

��ô����Ȼss_i = s2_i - s1_i * (n - i)��

ʱ�临�Ӷ�O((N + M)logN)��
